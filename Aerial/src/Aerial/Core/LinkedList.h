#pragma once

namespace aerial {

	template <typename T> struct single_node
	{
		single_node* next;
		T data;
	};

	template <typename T> struct singly_linked_list_iterator
	{
		using Node = single_node<T>;

		explicit singly_linked_list_iterator(Node* node) : m_node(node) {}

		bool operator==(const singly_linked_list_iterator& other) const { return m_node == other.m_node; }

		bool operator!=(const singly_linked_list_iterator& other) const { return m_node != other.m_node; }

		T& operator*() const { return m_node->data; }

		singly_linked_list_iterator& operator++()
		{
			m_node = m_node->next;
			return *this;
		}

		singly_linked_list_iterator operator++(int)
		{
			singly_linked_list_iterator it = *this;
			++*this;
			return it;
		}

	private:
		Node* m_node;
	};

	template <typename T> class singly_linked_list
	{
	public:
		using Iterator = singly_linked_list_iterator<T>;

		singly_linked_list() = default;
		singly_linked_list(singly_linked_list&&) = delete;
		singly_linked_list(const singly_linked_list& other)
		{
			auto node = other.m_Head;
			while (node)
			{
				PushBack(node->Data);
				node = node->Next;
			}
		}

		singly_linked_list& operator=(const singly_linked_list& other) {
			if (this == &other) return *this;
			clear();
			single_node<T>* current = other.m_Head;
			while (current) {
				PushBack(current->Data);
				current = current->Next;
			}
			return *this;
		}

		singly_linked_list& operator=(singly_linked_list&& other) noexcept {
			if (this == &other) return *this;
			clear();
			m_Head = other.m_Head;
			m_Tail = other.m_Tail;
			m_Size = other.m_Size;
			other.m_Head = nullptr;
			other.m_Tail = nullptr;
			other.m_Size = 0;
			return *this;
		}

		~singly_linked_list()
		{
			clear();
		}

		T head() const
		{
			AERIAL_ASSERT(m_Head, "Head is null");
			return m_Head->Data;
		}

		T tail() const
		{
			AERIAL_ASSERT(m_Tail, "Tail is null");
			return m_Tail->data;
		}

		Iterator begin() const { return Iterator(m_Head); }

		Iterator end() const { return Iterator(nullptr); }

		size_t size() const { return m_Size; }

		bool empty() const { return m_Size == 0; }

		void push_front(T data)
		{
			auto node = new single_node<T>{ m_Head, data };
			m_Head = node;
			if (not m_Tail) m_Tail = node;
			++m_Size;
		}

		T pop_front()
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

		void push_back(T data)
		{
			auto node = new single_node<T>{ nullptr, data };
			if (not m_Head) m_Head = node;
			if (not m_Tail) m_Tail = node;
			else
			{
				m_Tail->next = node;
				m_Tail = node;
			}
			++m_Size;
		}

		T pop_back()
		{
			if (not m_Tail || not m_Head) return nullptr;
			auto data = m_Tail->data;
			auto oldNode = m_Tail;

			if (m_Size == 1)
			{
				m_Head = nullptr;
				m_Tail = nullptr;
			}
			else
			{
				single_node<T>* node = m_Head;
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

		void clear()
		{
			while (m_Head)
			{
				auto node = m_Head;
				m_Head = m_Head->next;
				delete node;
			}
			m_Tail = nullptr;
			m_Size = 0;
		}

	protected:
		single_node<T>* m_Head { nullptr };
		single_node<T>* m_Tail { nullptr };
		size_t m_Size { 0 };
	};
}