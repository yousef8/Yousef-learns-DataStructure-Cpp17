#ifndef SPARSE_NODE_27052024_H
#define SPARSE_NODE_27052024_H

#include <iostream>
#include <memory>

struct Node
{
	int value;
	int idx;
	std::unique_ptr<Node> nxt;
	Node *prev;

	Node(int _value, int _idx) : value{_value}, idx{_idx}, nxt{nullptr}, prev{nullptr}
	{
	}

	~Node()
	{
		std::cout << "Destroy value: " << value << " @ idx " << idx << "\n";
	}
};

#endif