#pragma once

namespace Aerial {

	template <typename T> struct SingleNode
	{
		SingleNode* Next;
		T Data;
	};

	template <typename T> struct SinglyLinkedListIterator
	{
		using Node = SingleNode<T>;

		explicit SinglyLinkedListIterator(Node* node) : m_Node(node) {}

		bool operator==(const SinglyLinkedListIterator& other) const { return m_Node == other.m_Node; }

		bool operator!=(const SinglyLinkedListIterator& other) const { return m_Node != other.m_Node; }

		T& operator*() const { return m_Node->Data; }

		SinglyLinkedListIterator& operator++()
		{
			m_Node = m_Node->Next;
			return *this;
		}

		SinglyLinkedListIterator operator++(int)
		{
			SinglyLinkedListIterator it = *this;
			++*this;
			return it;
		}

	private:
		Node* m_Node;
	};

	template <typename T> class SinglyLinkedList
	{
	public:
		using Iterator = SinglyLinkedListIterator<T>;

		SinglyLinkedList() = default;
		SinglyLinkedList(SinglyLinkedList&&) = delete;
		SinglyLinkedList(const SinglyLinkedList& other)
		{
			auto node = other.m_Head;
			while (node)
			{
				PushBack(node->Data);
				node = node->Next;
			}
		}

		SinglyLinkedList& operator=(const SinglyLinkedList& other) {
			if (this == &other) return *this;
			Clear();
			SingleNode<T>* current = other.m_Head;
			while (current) {
				PushBack(current->Data);
				current = current->Next;
			}
			return *this;
		}

		SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
			if (this == &other) return *this;
			Clear();
			m_Head = other.m_Head;
			m_Tail = other.m_Tail;
			m_Size = other.m_Size;
			other.m_Head = nullptr;
			other.m_Tail = nullptr;
			other.m_Size = 0;
			return *this;
		}

		~SinglyLinkedList()
		{
			Clear();
		}

		T Head() const
		{
			AERIAL_ASSERT(m_Head, "Head is null");
			return m_Head->Data;
		}

		T Tail() const
		{
			AERIAL_ASSERT(m_Tail, "Tail is null");
			return m_Tail->Data;
		}

		Iterator begin() const { return Iterator(m_Head); }

		Iterator end() const { return Iterator(nullptr); }

		size_t Size() const { return m_Size; }

		bool Empty() const { return m_Size == 0; }

		void PushFront(T data)
		{
			auto node = new SingleNode<T>{ m_Head, data };
			m_Head = node;
			if (not m_Tail) m_Tail = node;
			++m_Size;
		}

		T PopFront()
		{
			if (not m_Head) return nullptr;
			auto data = m_Head->Data;
			auto oldNode = m_Head;
			m_Head = m_Head->Next;
			delete oldNode;
			--m_Size;
			if (m_Size == 0) m_Tail = nullptr;
			return data;
		}

		void PushBack(T data)
		{
			auto node = new SingleNode<T>{ nullptr, data };
			if (not m_Head) m_Head = node;
			if (not m_Tail) m_Tail = node;
			else
			{
				m_Tail->Next = node;
				m_Tail = node;
			}
			++m_Size;
		}

		T PopBack()
		{
			if (not m_Tail || not m_Head) return nullptr;
			auto data = m_Tail->Data;
			auto oldNode = m_Tail;

			if (m_Size == 1)
			{
				m_Head = nullptr;
				m_Tail = nullptr;
			}
			else
			{
				SingleNode<T>* node = m_Head;
				while (node->Next != m_Tail)
				{
					node = node->Next;
				}
				node->Next = nullptr;
				m_Tail = node;
			}
			delete oldNode;
			--m_Size;
			return data;
		}

		void Clear()
		{
			while (m_Head)
			{
				auto node = m_Head;
				m_Head = m_Head->Next;
				delete node;
			}
			m_Tail = nullptr;
			m_Size = 0;
		}

	protected:
		SingleNode<T>* m_Head { nullptr };
		SingleNode<T>* m_Tail { nullptr };
		size_t m_Size { 0 };
	};
}