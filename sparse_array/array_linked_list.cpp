#include <algorithm> //debug
#include <cassert>	 //debug
#include <iostream>
#include <memory>
#include <optional>
#include <sstream> //debug
#include <utility>
#include <vector> //debug

#include "sparse_node.hpp"

class ArrayLinkedList
{
  public:
	ArrayLinkedList(int _length) : head{nullptr}, tail{nullptr}, length{_length}
	{
	}

	void set_value(int value, int idx)
	{
		if (idx < 1 || idx > length)
		{
			std::cout << "Index ranges from 1 -> " << length << std::endl;
			return;
		}

		for (auto cur{head.get()}; cur; cur = cur->nxt.get())
		{
			if (idx <= cur->idx)
			{
				embed_before(cur, value, idx);
				return;
			}
		}

		insert_end(value, idx);
		return;
	}

	std::optional<int> get_value(int idx)
	{
		for (auto cur{head.get()}; cur; cur = cur->nxt.get())
		{
			if (idx <= cur->idx)
			{
				return cur->value;
			}
		}

		return std::nullopt;
	}

	void print_array_nonzero()
	{
		for (Node *cur{head.get()}; cur; cur = cur->nxt.get())
			std::cout << cur->value << " ";
		std::cout << std::endl;
		return;
	}

	void add(ArrayLinkedList &other)
	{
		Node *cur = head.get();
		Node *other_cur = other.head.get();

		while (cur && other_cur)
		{
			if (other_cur->idx < cur->idx)
			{
				embed_before(cur, other_cur->value, other_cur->idx);
				other_cur = other_cur->nxt.get();
				cur = cur->prev;
			}
			if (other_cur->idx == cur->idx)
			{
				cur->value += other_cur->value;
				other_cur = other_cur->nxt.get();
			}
			cur = cur->nxt.get();
		}

		while (other_cur)
		{
			insert_end(other_cur->value, other_cur->idx);
			other_cur = other_cur->nxt.get();
		}

		debug_verify_data_integrity();
		return;
	}

	friend std::ostream &operator<<(std::ostream &out, const ArrayLinkedList &ls)
	{
		int last_idx = 1;

		for (Node *cur{ls.head.get()}; cur; cur = cur->nxt.get())
		{
			while (last_idx++ < cur->idx)
			{
				out << "0 ";
			}
			out << cur->value << " ";
		}

		while (last_idx++ <= ls.length)
		{
			out << "0 ";
		}

		return out;
	}

  private:
	std::unique_ptr<Node> head;
	Node *tail;
	int length;

	void link(Node *head, Node *tail)
	{
		if (head)
			head->nxt.reset(tail);
		if (tail)
			tail->prev = head;
	}

	Node *embed_before(Node *cur, int value, int idx)
	{
		if (cur == head.get())
			return insert_front(value, idx);

		auto new_node = new Node(value, idx);
		add_node(new_node);
		Node *prev = cur->prev;

		// new_node <-> cur
		link(new_node, prev->nxt.release());

		// prev <-> new_node <->cur
		link(prev, new_node);

		debug_verify_data_integrity();
		return new_node;
	}

	Node *insert_end(int value, int idx)
	{
		Node *node = new Node{value, idx};
		add_node(node);
		link(tail, node);

		if (!head)
			head.reset(node);

		tail = node;

		debug_verify_data_integrity();
		return node;
	}

	Node *insert_front(int value, int idx)
	{
		auto node = new Node(value, idx);
		add_node(node);

		link(node, head.release());
		head.reset(node);
		if (!tail)
			tail = head.get();

		debug_verify_data_integrity();
		return node;
	}

	//====================================For Debugging Purposes====================================
	int debug_length{0};
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

	void print()
	{
		for (Node *cur{head.get()}; cur; cur = cur->nxt.get())
			std::cout << cur->value << " ";
		std::cout << "\n";
	}

	void print_reversed()
	{
		for (Node *cur{tail}; cur; cur = cur->prev)
			std::cout << cur->value << " <-> ";
		std::cout << "\n";
	}

	void debug_print_address()
	{
		for (Node *cur{head.get()}; cur; cur = cur->nxt.get())
			std::cout << cur << "," << cur->value << "\t";
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
			std::cout << node->prev->value << "\t";

		std::cout << " <= [" << node->value << "]\t => \t";

		if (node->nxt == nullptr)
			std::cout << "X\t";
		else
			std::cout << node->nxt->value << "\t";

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
		if (debug_length == 0)
			return "";
		std::ostringstream oss;
		for (Node *cur{head.get()}; cur; cur = cur->nxt.get())
		{
			oss << cur->value;
			if (cur->nxt)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity()
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
				assert(head.get() == tail);
			else
				assert(head.get() != tail);
			assert(!head->prev);
			assert(!tail->nxt);
		}
		int len = 0;
		for (Node *cur{head.get()}; cur; cur = cur->nxt.get(), len++)
		{
			if (len == debug_length - 1) // make sure we end at tail
				assert(cur == tail);
		}

		assert(debug_length == len);
		assert(debug_length == (int)debug_data.size());

		len = 0;
		for (Node *cur = tail; cur; cur = cur->prev, len++)
		{
			if (len == debug_length - 1) // make sure we end at head
				assert(cur == head.get());
		}
	}

	void delete_node(Node *node)
	{
		debug_remove_node(node);
		--debug_length;
	}

	void add_node(Node *node)
	{
		debug_add_node(node);
		++debug_length;
	}
	//====================================For Debugging Purposes====================================
};

int main()
{
	ArrayLinkedList array{10};
	array.set_value(50, 5);
	array.set_value(20, 2);
	array.set_value(70, 7);
	array.set_value(40, 4);
	std::cout << array << "\n";

	ArrayLinkedList arr2(10);
	arr2.set_value(1, 4);
	arr2.set_value(3, 7);
	arr2.set_value(4, 6);
	std::cout << arr2 << "\n";

	array.add(arr2);
	std::cout << array << "\n";

	return 0;
}