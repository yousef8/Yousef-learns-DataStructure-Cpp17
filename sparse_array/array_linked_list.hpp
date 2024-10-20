#ifndef ARRAY_LINKED_LIST_21102024_H
#define ARRAY_LINKED_LIST_21102024_H

#include "array_linked_list_debugger.hpp"
#include "sparse_node.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <utility>

template <typename T> class ArrayLinkedList
{
  public:
	ArrayLinkedList(int _length = 10) : length{_length}
	{
		auto node = new Node<T>(T(), -1);
		debugger.add_node(node);
		head.reset(node);
		tail = head.get();
		debug_verify_data_integrity();
	}

	ArrayLinkedList(const ArrayLinkedList &other) : ArrayLinkedList{other.length}
	{
		auto otherCurNode = other.head->nxt.get();
		while (otherCurNode)
		{
			embed_after(tail, otherCurNode->idx, otherCurNode->value);
			otherCurNode = otherCurNode->nxt.get();
		}
		debug_verify_data_integrity();
	}

	ArrayLinkedList &operator=(ArrayLinkedList other)
	{
		swap(*this, other);
		debug_verify_data_integrity();
		return *this;
	}

	ArrayLinkedList &operator+=(const ArrayLinkedList &other)
	{
		add(other);
		debug_verify_data_integrity();
		return *this;
	}

	void set_value(const T &value, int idx)
	{
		assert(idx > 0);
		assert(idx < length);

		auto node = get_idx(idx, true);
		node->value = value;
		debug_verify_data_integrity();
		return;
	}

	T get_value(int idx)
	{
		auto node = get_idx(idx);
		if (!node)
		{
			return T();
		}
		return node->value;
	}

	void print_array_nonzero()
	{
		auto cur_node{head->nxt.get()};
		while (cur_node)
		{
			std::cout << std::setw(4) << cur_node->value;
			cur_node = cur_node->nxt.get();
		}
		std::cout << std::endl;
	}

	void add(const ArrayLinkedList &other)
	{
		auto other_cur_node{other.head->nxt.get()};
		while (other_cur_node)
		{
			auto node = get_idx(other_cur_node->idx, true);
			node->value += other_cur_node->value;
			other_cur_node = other_cur_node->nxt.get();
		}
		debug_verify_data_integrity();
	}

	friend std::ostream &operator<<(std::ostream &out, const ArrayLinkedList<T> &ls)
	{
		auto cur{ls.head->nxt.get()};

		for (int count{0}; count < ls.length; ++count)
		{
			T value = T();
			if (cur && cur->idx == count)
			{
				value = cur->value;
				cur = cur->nxt.get();
			}
			out << std::setw(8) << value;
		}

		return out;
	}

	friend void swap(ArrayLinkedList &first, ArrayLinkedList &second)
	{
		using std::swap;
		std::swap(first.length, second.length);
		std::swap(first.head, second.head);
		std::swap(first.tail, second.tail);
		std::swap(first.debugger, second.debugger);
	}

  private:
	std::unique_ptr<Node<T>> head;
	Node<T> *tail;
	int length;
	ArrayLinkedListDebugger<T> debugger;

	void link(Node<T> *head, Node<T> *tail)
	{
		if (head)
			head->nxt.reset(tail);
		if (tail)
			tail->prv = head;
	}

	Node<T> *get_idx(int idx, bool create = false)
	{
		Node<T> *prv_node = head.get();

		while (prv_node->nxt && prv_node->nxt->idx < idx)
		{
			prv_node = prv_node->nxt.get();
		}

		bool found = prv_node->nxt && prv_node->nxt->idx == idx;

		if (found)
		{
			return prv_node->nxt.get();
		}

		if (create)
		{
			return embed_after(prv_node, idx);
		}

		return nullptr;
	}

	Node<T> *embed_after(Node<T> *node_before, int idx, T value = T())
	{
		auto middle = new Node(value, idx);
		debugger.add_node(middle);
		auto node_after = node_before->nxt.release();

		link(node_before, middle);
		link(middle, node_after);

		if (tail == node_before)
		{
			tail = middle;
		}

		debug_verify_data_integrity();

		return middle;
	}

	void debug_verify_data_integrity()
	{
		return debugger.debug_verify_data_integrity(head.get(), tail);
	}
};

template <typename T> ArrayLinkedList<T> operator+(ArrayLinkedList<T> lhs, const ArrayLinkedList<T> &rhs)
{
	return lhs += rhs;
}

#endif
