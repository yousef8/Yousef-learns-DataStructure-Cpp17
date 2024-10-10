#ifndef SPARSE_NODE_27052024_H
#define SPARSE_NODE_27052024_H

#include <iostream>
#include <memory>

struct Node
{
	int value;
	int idx;
	std::unique_ptr<Node> nxt;
	Node *prv;

	Node(int _value, int _idx) : value{_value}, idx{_idx}, nxt{nullptr}, prv{nullptr}
	{
	}

	~Node()
	{
		std::cout << "Destroy value: " << value << " @ idx " << idx << "\n";
	}
};

#endif
