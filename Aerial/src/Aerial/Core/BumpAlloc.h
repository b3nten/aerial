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
			char* m_Memory;
			size_t m_Size;
			size_t m_Used;
			size_t m_Remaining;

			Chunk(size_t size) : m_Size(size), m_Used(0), m_Remaining(size)
			{
				m_Memory = (char*)malloc(size);
			}

			~Chunk()
			{
				free(m_Memory);
			}
		};

	public:

		BumpAlloc(size_t chunkSize, size_t alignment = alignof(std::max_align_t)) : m_ChunkSize(chunkSize), m_Alignment(alignment)
		{
			auto initialChunk = new Chunk(chunkSize);
			m_Chunks.PushBack(initialChunk);
		}

		template <typename T>
		BumpAlloc(int capacity) { BumpAlloc(sizeof(T) * capacity); }

		~BumpAlloc()
		{
			for (auto chunk : m_Chunks)
			{
				delete chunk;
			}
		}

		char* Allocate(size_t size)
		{
			auto chunk = m_Chunks.Tail();
			if (chunk->m_Remaining < size)
			{
				chunk = new Chunk(m_ChunkSize);
				m_Chunks.PushBack(chunk);
			}

			auto start = chunk->m_Memory + chunk->m_Used;
			auto offset = (size_t)start % m_Alignment;
			auto padding = offset == 0 ? 0 : m_Alignment - offset;
			auto alignedStart = start + padding;

			chunk->m_Used += size + padding;
			chunk->m_Remaining -= size + padding;

			return alignedStart;
		};

		template <typename T>
		T* Allocate()
		{
			return (T*)Allocate(sizeof(T));
		}

		void Clear()
		{
			for (auto& chunk : m_Chunks)
			{
				chunk->m_Used = 0;
				chunk->m_Remaining = chunk->m_Size;
				memset(chunk->m_Memory, 0, chunk->m_Size);
			}
		}

	private:
		SinglyLinkedList<Chunk*> m_Chunks;
		size_t m_ChunkSize;
		size_t m_Alignment;
	};
}