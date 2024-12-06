#pragma once
#include "Core.h"
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

namespace Aerial
{
	class BumpAlloc
	{
		struct Chunk
		{
			std::byte* m_Memory;
			size_t m_Size;
			size_t m_Used;

			Chunk(size_t size) : m_Size(size), m_Used(0)
			{
				m_Memory = (std::byte*)malloc(size);
				if(not m_Memory) throw std::bad_alloc();
			}

			~Chunk()
			{
				free((void*)m_Memory);
			}
		};

	public:

		bool m_AllowOversizedAllocations = false;

		BumpAlloc(size_t chunkSize, size_t alignment = alignof(std::max_align_t)) : m_ChunkSize(chunkSize), m_Alignment(alignment)
		{
			if(chunkSize == 0)
			{
				AERIAL_ASSERT(false, "Chunk size must be greater than 0");
				m_ChunkSize = 1024;
			}

			if((alignment & (alignment - 1)) != 0)
			{
				AERIAL_ASSERT(false, "Alignment must be a power of 2");
				m_Alignment = alignof(std::max_align_t);
			}

			auto initialChunk = new Chunk(m_ChunkSize);
			m_Chunks.PushBack(initialChunk);
		}

		template <typename T>
		BumpAlloc(int capacity) : BumpAlloc(sizeof(T) * capacity) {}

		~BumpAlloc()
		{
			for (auto chunk : m_Chunks)
			{
				delete chunk;
			}
		}

		void* Allocate(size_t size)
		{
			auto chunk = m_Chunks.Tail();

			if(size > m_ChunkSize)
			{
				if(not m_AllowOversizedAllocations)
				{
					AERIAL_ASSERT(false, "Allocation size is larger than chunk size");
				}
				AERIAL_LOG_WARN("Allocation size is larger than chunk size");
				chunk = new Chunk(size);
				// Add new chunk to the front of the list, as it's a one-off allocation.
				m_Chunks.PushFront(chunk);
			}

			void* currentPosPointer = chunk->m_Memory + chunk->m_Used;
			size_t remaining = chunk->m_Size - chunk->m_Used;

			void* alignedPointer = std::align(m_Alignment, size, currentPosPointer, remaining);

			if(not alignedPointer)
			{
				// Allocate a new chunk
				m_Chunks.PushBack(new Chunk(m_ChunkSize));
				chunk = m_Chunks.Tail();
				currentPosPointer = chunk->m_Memory;
				remaining = chunk->m_Size;
				alignedPointer = std::align(m_Alignment, size, currentPosPointer, remaining);
				AERIAL_ASSERT(alignedPointer, "Failed to align memory in new chunk");
			}

			chunk->m_Used = (size_t) ( (std::byte*)alignedPointer - chunk->m_Memory ) + size;
			return alignedPointer;
		};

		template <typename T, typename ...Args>
		T* Make(Args&& ...args)
		{
			return new (Allocate(sizeof(T))) T(std::forward<Args>(args)...);
		}

		void Clear()
		{
			for (auto& chunk : m_Chunks)
			{
				chunk->m_Used = 0;
				memset(chunk->m_Memory, 0, chunk->m_Size);
			}
		}

	private:
		SinglyLinkedList<Chunk*> m_Chunks;
		size_t m_ChunkSize;
		size_t m_Alignment;
	};
}