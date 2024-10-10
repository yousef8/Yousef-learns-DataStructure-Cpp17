#include <algorithm> //debug
#include <cassert>	 //debug
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream> //debug
#include <vector>  //debug

#include "sparse_node.hpp"

class ArrayLinkedList
{
  public:
	ArrayLinkedList(int _length) : length{_length}
	{
		auto node = new Node(0, -1);
		add_node(node);
		head.reset(node);
		tail = head.get();
		debug_verify_data_integrity();
	}

	void set_value(int value, int idx)
	{
		assert(idx > 0);
		assert(idx < length);

		auto node = get_idx(idx, true);
		node->value = value;
		return;
	}

	int get_value(int idx)
	{
		auto node = get_idx(idx);
		if (!node)
		{
			return 0;
		}
		return node->idx;
	}

	void print_array_nonzero()
	{
		auto cur_node{head.get()};
		while (cur_node)
		{
			std::cout << std::setw(4) << cur_node->value;
			cur_node = cur_node->nxt.get();
		}
		std::cout << std::endl;
	}

	void add(ArrayLinkedList &other)
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

	friend std::ostream &operator<<(std::ostream &out, const ArrayLinkedList &ls)
	{
		Node *cur{ls.head->nxt.get()};

		for (int count{0}; count < ls.length; ++count)
		{
			int value = 0;
			if (cur && cur->idx == count)
			{
				value = cur->value;
				cur = cur->nxt.get();
			}
			out << std::setw(4) << value;
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
			tail->prv = head;
	}

	Node *get_idx(int idx, bool create = false)
	{
		Node *prv_node = head.get();

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

	Node *embed_after(Node *node_before, int idx, int value = 0)
	{
		auto middle = new Node(value, idx);
		add_node(middle);
		auto node_after = node_before->nxt.release();

		link(node_before, middle);
		link(middle, node_after);

		if (tail == node_before)
		{
			tail = middle;
		}

		return middle;
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
		for (Node *cur{tail}; cur; cur = cur->prv)
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

		if (node->prv == nullptr)
			std::cout << "X\t";
		else
			std::cout << node->prv->value << "\t";

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
			assert(!head->prv);
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
		for (Node *cur = tail; cur; cur = cur->prv, len++)
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
	std::cout << "Array 1 : ";
	array.print_array_nonzero();

	ArrayLinkedList arr2(10);
	arr2.set_value(1, 4);
	arr2.set_value(3, 7);
	arr2.set_value(4, 6);
	std::cout << "Array 2 : ";
	arr2.print_array_nonzero();

	std::cout << array << "\n";
	std::cout << arr2 << "\n";
	array.add(arr2);
	std::cout << array << "\n";

	return 0;
}