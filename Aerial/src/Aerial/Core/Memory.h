#pragma once
#include "Core.h"
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

namespace aerial
{
	class bump_alloc
	{
		struct chunk
		{
			std::byte* m_memory;
			size_t m_size;
			size_t m_used;

			chunk(size_t size) : m_size(size), m_used(0)
			{
				m_memory = (std::byte*)malloc(size);
				if(not m_memory) throw std::bad_alloc();
			}

			~chunk()
			{
				free((void*)m_memory);
			}
		};

	public:

		bool m_AllowOversizedAllocations = false;

		bump_alloc(size_t chunk_size, size_t alignment = alignof(std::max_align_t)) : m_chunk_size(chunk_size), m_alignment(alignment)
		{
			if(chunk_size == 0)
			{
				AERIAL_ASSERT(false, "Chunk size must be greater than 0");
				m_chunk_size = 1024;
			}

			if((alignment & (alignment - 1)) != 0)
			{
				AERIAL_ASSERT(false, "Alignment must be a power of 2");
				m_alignment = alignof(std::max_align_t);
			}

			auto initial_chunk = new chunk(m_chunk_size);
			m_chunks.push_back(initial_chunk);
		}

		template <typename T>
		bump_alloc(int capacity) : bump_alloc(sizeof(T) * capacity) {}

		~bump_alloc()
		{
			for (auto chunk : m_chunks)
			{
				delete chunk;
			}
		}

		void* allocate(size_t size)
		{
			auto new_chunk = m_chunks.tail();

			if(size > m_chunk_size)
			{
				if(not m_AllowOversizedAllocations)
				{
					AERIAL_ASSERT(false, "Allocation size is larger than chunk size");
				}
				AERIAL_LOG_WARN("Allocation size is larger than chunk size");
				new_chunk = new chunk(size);
				// Add new chunk to the front of the list, as it's a one-off allocation.
				m_chunks.push_front(new_chunk);
			}

			void* currentPosPointer = new_chunk->m_memory + new_chunk->m_used;
			size_t remaining = new_chunk->m_size - new_chunk->m_used;

			void* alignedPointer = std::align(m_alignment, size, currentPosPointer, remaining);

			if(not alignedPointer)
			{
				// Allocate a new chunk
				m_chunks.push_back(new chunk(m_chunk_size));
				new_chunk = m_chunks.tail();
				currentPosPointer = new_chunk->m_memory;
				remaining = new_chunk->m_size;
				alignedPointer = std::align(m_alignment, size, currentPosPointer, remaining);
				AERIAL_ASSERT(alignedPointer, "Failed to align memory in new chunk");
			}

			new_chunk->m_used = (size_t) ( (std::byte*)alignedPointer - new_chunk->m_memory ) + size;
			return alignedPointer;
		};

		template <typename T, typename ...Args>
		T* make(Args&& ...args)
		{
			return new (allocate(sizeof(T))) T(std::forward<Args>(args)...);
		}

		void clear()
		{
			for (auto& chunk : m_chunks)
			{
				chunk->m_used = 0;
				memset(chunk->m_memory, 0, chunk->m_size);
			}
		}

	private:
		singly_linked_list<chunk*> m_chunks;
		size_t m_chunk_size;
		size_t m_alignment;
	};

}