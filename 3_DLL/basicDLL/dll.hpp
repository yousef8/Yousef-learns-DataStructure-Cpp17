#ifndef DLL_2872023_H
#define DLL_2872023_H

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Node
{
	std::unique_ptr<Node> next;
	int data;
	Node *prev;

	Node(int data) : data{data}, next{nullptr}, prev{nullptr}
	{
	}

	void set(std::unique_ptr<Node> _next, Node *_prev)
	{
		next = std::move(_next);
		prev = _prev;
	}

	~Node()
	{
		std::cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class BasicDLL
{
  protected:
	std::unique_ptr<Node> head{};
	Node *tail{};

	void link(Node *head, Node *tail)
	{
		if (head)
			head->next.reset(tail);
		if (tail)
			tail->prev = head;
	}

	Node *delete_and_link(Node *to_be_deleted)
	{
		Node *prev = to_be_deleted->prev;
		link(to_be_deleted->prev, to_be_deleted->next.release());
		delete_node(to_be_deleted);
		return prev;
	}

	// For debugging purposes
	// courtesy of course instructor

	int length{0};
	std::vector<Node *> debug_data;

	void debug_add_node(Node *node)
	{
		debug_data.push_back(node);
	}

	void debug_remove_node(Node *node)
	{
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			std::cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

  public:
	BasicDLL() = default;

	BasicDLL(const std::initializer_list<int> &lst)
	{
		for (int value : lst)
			insert_end(value);
	}

	BasicDLL(const BasicDLL &) = delete;
	BasicDLL &operator=(const BasicDLL &other) = delete;

	// For Debugging purposes
	void print()
	{
		for (Node *cur{head.get()}; cur; cur = cur->next.get())
			std::cout << cur->data << " ";
		std::cout << "\n";
	}

	void print_reversed()
	{
		for (Node *cur{tail}; cur; cur = cur->prev)
			std::cout << cur->data << " <-> ";
		std::cout << "\n";
	}

	void debug_print_address()
	{
		for (Node *cur{head.get()}; cur; cur = cur->next.get())
			std::cout << cur << "," << cur->data << "\t";
		std::cout << "\n";
	}

	void debug_print_node(Node *node, bool is_seperate = false)
	{
		if (is_seperate)
			std::cout << "Sep: ";
		if (node == nullptr)
		{
			std::cout << "nullptr\n";
			return;
		}

		if (node->prev == nullptr)
			std::cout << "X\t";
		else
			std::cout << node->prev->data << "\t";

		std::cout << " <= [" << node->data << "]\t => \t";

		if (node->next == nullptr)
			std::cout << "X\t";
		else
			std::cout << node->next->data << "\t";

		if (node == head.get())
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

	std::string debug_to_string()
	{
		if (length == 0)
			return "";
		std::ostringstream oss;
		for (Node *cur{head.get()}; cur; cur = cur->next.get())
		{
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity()
	{
		if (length == 0)
		{
			assert(head == nullptr);
			assert(tail == nullptr);
		}
		else
		{
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head.get() == tail);
			else
				assert(head.get() != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node *cur{head.get()}; cur; cur = cur->next.get(), len++)
		{
			if (len == length - 1) // make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int)debug_data.size());

		len = 0;
		for (Node *cur = tail; cur; cur = cur->prev, len++)
		{
			if (len == length - 1) // make sure we end at head
				assert(cur == head.get());
		}
	}

	void delete_node(Node *node)
	{
		debug_remove_node(node);
		--length;
	}

	void add_node(Node *node)
	{
		debug_add_node(node);
		++length;
	}
	////////////////////////////////////////////////////////////

	void insert_end(int value)
	{
		Node *node = new Node{value};
		add_node(node);
		link(tail, node);

		if (!head)
			head.reset(node);

		tail = node;

		debug_verify_data_integrity();
	}

	void insert_front(int value)
	{
		auto node = std::make_unique<Node>(value);
		add_node(node.get());
		link(node.get(), head.release());
		head.reset(node.release());
		if (!tail)
			tail = head.get();

		debug_verify_data_integrity();
	}

	void embed_before(Node *cur, int value)
	{
		if (cur == head.get())
			return insert_front(value);

		auto new_node = std::make_unique<Node>(value);
		add_node(new_node.get());
		Node *prev = cur->prev;

		// new_node <-> cur
		link(new_node.get(), prev->next.release());
		// same as
		// new_node->next.reset(prev->next.release());
		// cur->prev = new_node.get();

		// prev <-> new_node <->cur
		link(prev, new_node.release());
		// same as
		// new_node->prev = prev;
		// prev->next.reset(new_node.release());

		debug_verify_data_integrity();
		return;
	}

	void insert_sorted(int value)
	{
		for (auto cur{head.get()}; cur; cur = cur->next.get())
			if (value <= cur->data)
				return embed_before(cur, value);

		return insert_end(value);
	}

	friend std::ostream &operator<<(std::ostream &out, const BasicDLL &ls)
	{
		out << " X <-> ";

		for (Node *cur{ls.head.get()}; cur; cur = cur->next.get())
			out << cur->data << " <-> ";

		out << "X ";

		return out;
	}

	void delete_front()
	{
		// if the BasicDLL is empty
		if (head.get() == tail && !head)
			return;

		delete_node(head.get());
		head.reset(head->next.release());
		if (head)
			head->prev = nullptr;
		else
			tail = nullptr;

		debug_verify_data_integrity();
	}

	void delete_end()
	{
		if (head.get() == tail)
			return delete_front();

		Node *old_tail = tail;
		tail = tail->prev;

		old_tail->prev->next.reset();
		delete_node(old_tail);

		debug_verify_data_integrity();
	}

	void delete_a_node(Node *to_be_deleted)
	{
		if (to_be_deleted == head.get())
			return delete_front();
		else if (to_be_deleted == tail)
			return delete_end();
		else
			delete_and_link(to_be_deleted);
		return;
	}

	void delete_node_with_key(int value)
	{
		for (Node *cur{head.get()}; cur; cur = cur->next.get())
		{
			if (cur->data == value)
			{
				if (cur == head.get())
					return delete_front();
				if (cur == tail)
					return delete_end();
				delete_and_link(cur);
				debug_verify_data_integrity();
				return;
			}
		}
	}
};

#endif
