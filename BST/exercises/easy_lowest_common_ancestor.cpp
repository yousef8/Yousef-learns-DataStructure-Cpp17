#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"

class LCA : public BST<LCA> {
  public:
	using BST<LCA>::BST;

	LCA *lca(int x, int y) {
		if (x < data && y < data)
			return left->lca(x, y);

		if (x > data && y > data)
			return right->lca(x, y);

		return this;
	}
};

int main() {
	TestSuite<int> ts;

	ts.addTest(
		"Simple tree: LCA(3, 7) in tree with root 5",
		[]() {
			LCA *tree = new LCA(5);
			tree->insert(3);
			tree->insert(7);
			LCA *result = tree->lca(3, 7);
			int data = result->getData();
			delete tree;
			return data;
		},
		5);

	ts.addTest(
		"Left subtree: LCA(1, 3) in tree [5, 3, 7, 1]",
		[]() {
			LCA *tree = new LCA(5);
			tree->insert(3);
			tree->insert(7);
			tree->insert(1);
			LCA *result = tree->lca(1, 3);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Right subtree: LCA(7, 9) in tree [5, 3, 7, 9]",
		[]() {
			LCA *tree = new LCA(5);
			tree->insert(3);
			tree->insert(7);
			tree->insert(9);
			LCA *result = tree->lca(7, 9);
			int data = result->getData();
			delete tree;
			return data;
		},
		7);

	ts.addTest(
		"Ancestor case: LCA(3, 1) where 3 is ancestor of 1",
		[]() {
			LCA *tree = new LCA(5);
			tree->insert(3);
			tree->insert(7);
			tree->insert(1);
			LCA *result = tree->lca(3, 1);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Ancestor case: LCA(7, 9) where 7 is ancestor of 9",
		[]() {
			LCA *tree = new LCA(5);
			tree->insert(3);
			tree->insert(7);
			tree->insert(9);
			LCA *result = tree->lca(7, 9);
			int data = result->getData();
			delete tree;
			return data;
		},
		7);

	ts.addTest(
		"Root ancestor: LCA(5, 1) where root is ancestor",
		[]() {
			LCA *tree = new LCA(5);
			tree->insert(3);
			tree->insert(7);
			tree->insert(1);
			LCA *result = tree->lca(5, 1);
			int data = result->getData();
			delete tree;
			return data;
		},
		5);

	ts.addTest(
		"Balanced tree: LCA(1, 4) in balanced tree",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(3);
			tree->insert(7);
			tree->insert(1);
			tree->insert(4);
			LCA *result = tree->lca(1, 4);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Balanced tree: LCA(3, 7) should be 5",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(3);
			tree->insert(7);
			LCA *result = tree->lca(3, 7);
			int data = result->getData();
			delete tree;
			return data;
		},
		5);

	ts.addTest(
		"Left-skewed tree: LCA(1, 3) should be 3",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(8);
			tree->insert(6);
			tree->insert(4);
			tree->insert(3);
			tree->insert(1);
			LCA *result = tree->lca(1, 3);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Right-skewed tree: LCA(3, 5) should be 3",
		[]() {
			LCA *tree = new LCA(1);
			tree->insert(2);
			tree->insert(3);
			tree->insert(4);
			tree->insert(5);
			LCA *result = tree->lca(3, 5);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Large tree: LCA(2, 18) at root",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(2);
			tree->insert(7);
			tree->insert(12);
			tree->insert(18);
			LCA *result = tree->lca(2, 18);
			int data = result->getData();
			delete tree;
			return data;
		},
		10);

	ts.addTest(
		"Deep nodes: LCA(6, 8) in complex tree",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(3);
			tree->insert(7);
			tree->insert(6);
			tree->insert(8);
			LCA *result = tree->lca(6, 8);
			int data = result->getData();
			delete tree;
			return data;
		},
		7);

	ts.addTest(
		"Adjacent leaves: LCA(6, 8) with parent 7",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(7);
			tree->insert(6);
			tree->insert(8);
			LCA *result = tree->lca(6, 8);
			int data = result->getData();
			delete tree;
			return data;
		},
		7);

	ts.addTest(
		"Complete tree: LCA(20, 40) should be 30",
		[]() {
			LCA *tree = new LCA(50);
			tree->insert(30);
			tree->insert(70);
			tree->insert(20);
			tree->insert(40);
			tree->insert(60);
			tree->insert(80);
			LCA *result = tree->lca(20, 40);
			int data = result->getData();
			delete tree;
			return data;
		},
		30);

	ts.addTest(
		"Cross-subtree: LCA(20, 80) at root",
		[]() {
			LCA *tree = new LCA(50);
			tree->insert(30);
			tree->insert(70);
			tree->insert(20);
			tree->insert(40);
			tree->insert(60);
			tree->insert(80);
			LCA *result = tree->lca(20, 80);
			int data = result->getData();
			delete tree;
			return data;
		},
		50);

	ts.addTest(
		"Different depths: LCA(1, 4) where nodes at different levels",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(3);
			tree->insert(7);
			tree->insert(1);
			tree->insert(4);
			tree->insert(6);
			LCA *result = tree->lca(1, 4);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Direct root LCA: LCA(5, 15) with root 10",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(3);
			tree->insert(7);
			tree->insert(12);
			tree->insert(20);
			LCA *result = tree->lca(5, 15);
			int data = result->getData();
			delete tree;
			return data;
		},
		10);

	ts.addTest(
		"Both leaves left: LCA(1, 4) as leaves",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(3);
			tree->insert(7);
			tree->insert(1);
			tree->insert(4);
			LCA *result = tree->lca(1, 4);
			int data = result->getData();
			delete tree;
			return data;
		},
		3);

	ts.addTest(
		"Both leaves right: LCA(12, 18) as leaves",
		[]() {
			LCA *tree = new LCA(10);
			tree->insert(5);
			tree->insert(15);
			tree->insert(12);
			tree->insert(18);
			LCA *result = tree->lca(12, 18);
			int data = result->getData();
			delete tree;
			return data;
		},
		15);

	ts.addTest(
		"Three-level: LCA(11, 14) in subtree",
		[]() {
			LCA *tree = new LCA(20);
			tree->insert(10);
			tree->insert(30);
			tree->insert(5);
			tree->insert(15);
			tree->insert(11);
			tree->insert(14);
			LCA *result = tree->lca(11, 14);
			int data = result->getData();
			delete tree;
			return data;
		},
		11);

	ts.run();

	return 0;
}
