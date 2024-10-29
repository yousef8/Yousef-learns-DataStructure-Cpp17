#ifndef SPARSE_NODE_27052024_H
#define SPARSE_NODE_27052024_H

#include <memory>

template <typename T> struct Node
{
	T value;
	int idx;
	std::unique_ptr<Node> nxt;
	Node *prv;

	Node(T _value, int _idx) : value{_value}, idx{_idx}, nxt{nullptr}, prv{nullptr}
	{
	}
};

#endif
