#ifndef ARRAY_LINKED_LIST_DEBUGGER_21102024_H
#define ARRAY_LINKED_LIST_DEBUGGER_21102024_H

#include "sparse_node.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T> class ArrayLinkedListDebugger
{
  public:
	void add_node(Node<T> *node)
	{
		debug_add_node(node);
		++debug_length;
	}

	void debug_add_node(Node<T> *node)
	{
		debug_data.push_back(node);
	}

	void delete_node(Node<T> *node)
	{
		debug_remove_node(node);
		--debug_length;
	}

	void debug_remove_node(Node<T> *node)
	{
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			std::cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

	void print(Node<T> *head)
	{
		for (auto cur{head}; cur; cur = cur->nxt.get())
			std::cout << cur->value << " ";
		std::cout << "\n";
	}

	void print_reversed(Node<T> *tail)
	{
		for (auto cur{tail}; cur; cur = cur->prv)
			std::cout << cur->value << " <-> ";
		std::cout << "\n";
	}

	void debug_print_address(Node<T> *head)
	{
		for (auto cur{head}; cur; cur = cur->nxt.get())
			std::cout << cur << "," << cur->value << "\t";
		std::cout << "\n";
	}

	void debug_print_node(Node<T> *head, Node<T> *tail, Node<T> *node, bool is_seperate = false)
	{
		if (is_seperate)
			std::cout << "Sep: ";
		if (node == nullptr)
		{
			std::cout << "nullptr\n";
			return;
		}

		if (node->prv == nullptr)
			std::cout << "X\t";
		else
			std::cout << node->prv->value << "\t";

		std::cout << " <= [" << node->value << "]\t => \t";

		if (node->nxt == nullptr)
			std::cout << "X\t";
		else
			std::cout << node->nxt->value << "\t";

		if (node == head)
			std::cout << "head\n";
		else if (node == tail)
			std::cout << "tail\n";
		else
			std::cout << "\n";
	}
	void debug_print_list(std::string msg = "")
	{
		if (msg != "")
			std::cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		std::cout << "************\n" << std::flush;
	}

	std::string debug_to_string(Node<T> *head)
	{
		if (debug_length == 0)
			return "";
		std::ostringstream oss;
		for (auto cur{head}; cur; cur = cur->nxt.get())
		{
			oss << cur->value;
			if (cur->nxt)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity(Node<T> *head, Node<T> *tail)
	{
		if (debug_length == 0)
		{
			assert(head == nullptr);
			assert(tail == nullptr);
		}
		else
		{
			assert(head != nullptr);
			assert(tail != nullptr);
			if (debug_length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prv);
			assert(!tail->nxt);
		}
		int len = 0;
		for (Node<T> *cur{head}; cur; cur = cur->nxt.get(), len++)
		{
			if (len == debug_length - 1) // make sure we end at tail
				assert(cur == tail);
		}

		assert(debug_length == len);
		assert(debug_length == (int)debug_data.size());

		len = 0;
		for (auto cur = tail; cur; cur = cur->prv, len++)
		{
			if (len == debug_length - 1) // make sure we end at head
				assert(cur == head);
		}
	}

  private:
	int debug_length{0};
	std::vector<Node<T> *> debug_data;
};

#endif
