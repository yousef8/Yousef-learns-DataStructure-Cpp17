#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <cctype>
#include <stack>
#include <string>

class ExpressionTree : public BinaryTree<ExpressionTree, std::string> {
  public:
	ExpressionTree(const std::string &postfix)
		: BinaryTree<ExpressionTree, std::string>("0") {

		if (postfix.size() == 1) {
			data = postfix;
			return;
		}

		auto result = buildTree(postfix);
		data = result.node->data;
		left = result.node->left;
		right = result.node->right;
	}

	std::string printPostOrder() const {
		std::string result;
		if (left) {
			result += left->printPostOrder();
		}
		if (right) {
			result += right->printPostOrder();
		}
		result += data;
		return result;
	}

	std::string printInOrder() const {
		std::string result;

		if (left || right) {
			result += "(";
		}

		if (left) {
			result += left->printInOrder();
		}

		result += data;

		if (right) {
			result += right->printInOrder();
		}

		if (left || right) {
			result += ")";
		}

		return result;
	}

  private:
	struct ParseResult {
		ExpressionTree *node;
		std::string remaining;
	};

	ParseResult buildTree(const std::string &postfix) {
		if (postfix.empty()) {
			return ParseResult{nullptr, postfix};
		}

		auto postfix_local = postfix;
		auto op = postfix_local.back();
		postfix_local.pop_back();

		ExpressionTree *node = new ExpressionTree(std::string{op});

		if (!postfix_local.empty()) {
			auto rightOperand = postfix_local.back();

			if (std::isdigit(rightOperand)) {
				ExpressionTree *rightNode =
					new ExpressionTree(std::string{rightOperand});
				node->right = rightNode;
				postfix_local.pop_back();
			} else {
				auto rightParse = buildTree(postfix_local);
				node->right = rightParse.node;
				postfix_local = rightParse.remaining;
			}
		}

		if (!postfix_local.empty()) {
			auto leftOperand = postfix_local.back();
			if (std::isdigit(leftOperand)) {
				ExpressionTree *leftNode =
					new ExpressionTree(std::string{leftOperand});
				node->left = leftNode;
				postfix_local.pop_back();
			} else {
				auto rightParse = buildTree(postfix_local);
				node->left = rightParse.node;
				postfix_local = rightParse.remaining;
			}
		}

		return ParseResult{node, postfix_local};
	}
};

int main() {
	TestSuite<std::string> postOrderSuite;

	postOrderSuite.addTest(
		"Simple addition",
		[]() {
			ExpressionTree tree("23+");
			return tree.printPostOrder();
		},
		"23+");

	postOrderSuite.addTest(
		"Simple subtraction",
		[]() {
			ExpressionTree tree("52-");
			return tree.printPostOrder();
		},
		"52-");

	postOrderSuite.addTest(
		"Simple multiplication",
		[]() {
			ExpressionTree tree("34*");
			return tree.printPostOrder();
		},
		"34*");

	postOrderSuite.addTest(
		"Simple division",
		[]() {
			ExpressionTree tree("84/");
			return tree.printPostOrder();
		},
		"84/");

	postOrderSuite.addTest(
		"Multiple operations left-heavy",
		[]() {
			ExpressionTree tree("23+4*");
			return tree.printPostOrder();
		},
		"23+4*");

	postOrderSuite.addTest(
		"Multiple operations right-heavy",
		[]() {
			ExpressionTree tree("234*+");
			return tree.printPostOrder();
		},
		"234*+");

	postOrderSuite.addTest(
		"Mixed operations",
		[]() {
			ExpressionTree tree("23*45*+");
			return tree.printPostOrder();
		},
		"23*45*+");

	postOrderSuite.addTest(
		"Complex expression with all operators",
		[]() {
			ExpressionTree tree("23+45-*6/");
			return tree.printPostOrder();
		},
		"23+45-*6/");

	postOrderSuite.addTest(
		"Mixed single and multi-digit",
		[]() {
			ExpressionTree tree("5 10 + 3 *");
			return tree.printPostOrder();
		},
		"5 10 + 3 *");

	postOrderSuite.addTest(
		"Long expression",
		[]() {
			ExpressionTree tree("234*+56*-");
			return tree.printPostOrder();
		},
		"234*+56*-");

	postOrderSuite.addTest(
		"Very long expression",
		[]() {
			ExpressionTree tree("23+45+*67+*");
			return tree.printPostOrder();
		},
		"23+45+*67+*");

	postOrderSuite.addTest(
		"Single operand",
		[]() {
			ExpressionTree tree("5");
			return tree.printPostOrder();
		},
		"5");

	postOrderSuite.addTest(
		"Expression equivalent to (2+3)*4",
		[]() {
			ExpressionTree tree("23+4*");
			return tree.printPostOrder();
		},
		"23+4*");

	postOrderSuite.addTest(
		"Expression equivalent to 2+(3*4)",
		[]() {
			ExpressionTree tree("234*+");
			return tree.printPostOrder();
		},
		"234*+");

	postOrderSuite.addTest(
		"Expression equivalent to ((2+3)*(4-5))/6",
		[]() {
			ExpressionTree tree("23+45-*6/");
			return tree.printPostOrder();
		},
		"23+45-*6/");

	postOrderSuite.addTest(
		"Arithmetic expression 1",
		[]() {
			ExpressionTree tree("52/3*84/-");
			return tree.printPostOrder();
		},
		"52/3*84/-");

	postOrderSuite.addTest(
		"Arithmetic expression 2",
		[]() {
			ExpressionTree tree("92-35*-");
			return tree.printPostOrder();
		},
		"92-35*-");

	postOrderSuite.run();

	// InOrder tests
	TestSuite<std::string> inOrderSuite;

	inOrderSuite.addTest(
		"Simple addition",
		[]() {
			ExpressionTree tree("23+");
			return tree.printInOrder();
		},
		"(2+3)");

	inOrderSuite.addTest(
		"Simple subtraction",
		[]() {
			ExpressionTree tree("52-");
			return tree.printInOrder();
		},
		"(5-2)");

	inOrderSuite.addTest(
		"Simple multiplication",
		[]() {
			ExpressionTree tree("34*");
			return tree.printInOrder();
		},
		"(3*4)");

	inOrderSuite.addTest(
		"Simple division",
		[]() {
			ExpressionTree tree("84/");
			return tree.printInOrder();
		},
		"(8/4)");

	inOrderSuite.addTest(
		"Multiple operations left-heavy",
		[]() {
			ExpressionTree tree("23+4*");
			return tree.printInOrder();
		},
		"((2+3)*4)");

	inOrderSuite.addTest(
		"Multiple operations right-heavy",
		[]() {
			ExpressionTree tree("234*+");
			return tree.printInOrder();
		},
		"(2+(3*4))");

	inOrderSuite.addTest(
		"Mixed operations",
		[]() {
			ExpressionTree tree("23*45*+");
			return tree.printInOrder();
		},
		"((2*3)+(4*5))");

	inOrderSuite.addTest(
		"Complex expression with all operators",
		[]() {
			ExpressionTree tree("23+45-*6/");
			return tree.printInOrder();
		},
		"(((2+3)*(4-5))/6)");

	inOrderSuite.addTest(
		"Mixed single and multi-digit",
		[]() {
			ExpressionTree tree("5 10 + 3 *");
			return tree.printInOrder();
		},
		"(*(( (( 5)+(1 0))) 3))");

	inOrderSuite.addTest(
		"Long expression",
		[]() {
			ExpressionTree tree("234*+56*-");
			return tree.printInOrder();
		},
		"((2+(3*4))-(5*6))");

	inOrderSuite.addTest(
		"Very long expression",
		[]() {
			ExpressionTree tree("23+45+*67+*");
			return tree.printInOrder();
		},
		"(((2+3)*(4+5))*(6+7))");

	inOrderSuite.addTest(
		"Single operand",
		[]() {
			ExpressionTree tree("5");
			return tree.printInOrder();
		},
		"5");

	inOrderSuite.addTest(
		"Expression equivalent to (2+3)*4",
		[]() {
			ExpressionTree tree("23+4*");
			return tree.printInOrder();
		},
		"((2+3)*4)");

	inOrderSuite.addTest(
		"Expression equivalent to 2+(3*4)",
		[]() {
			ExpressionTree tree("234*+");
			return tree.printInOrder();
		},
		"(2+(3*4))");

	inOrderSuite.addTest(
		"Expression equivalent to ((2+3)*(4-5))/6",
		[]() {
			ExpressionTree tree("23+45-*6/");
			return tree.printInOrder();
		},
		"(((2+3)*(4-5))/6)");

	inOrderSuite.addTest(
		"Arithmetic expression 1",
		[]() {
			ExpressionTree tree("52/3*84/-");
			return tree.printInOrder();
		},
		"(((5/2)*3)-(8/4))");

	inOrderSuite.addTest(
		"Arithmetic expression 2",
		[]() {
			ExpressionTree tree("92-35*-");
			return tree.printInOrder();
		},
		"((9-2)-(3*5))");

	inOrderSuite.run();
	return 0;
}