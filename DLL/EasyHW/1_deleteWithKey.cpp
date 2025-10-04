#include "../include/dll.hpp"

class DLLExtended : public Dll {
  public:
	DLLExtended() = default;

	DLLExtended(const std::initializer_list<int> &lst) : Dll{lst} {}

	DLLExtended(const DLLExtended &) = delete;
	DLLExtended &operator=(const DLLExtended &other) = delete;

	void delete_all_nodes_with_key(int value) {
		for (Node *cur{head.get()}; cur;) {
			Node *to_be_deleted = cur;
			cur = cur->next.get();
			if (to_be_deleted->data == value)
				delete_a_node(to_be_deleted);
		}
	}
};

void delete_all_nodes_with_key_test() {
	std::cout << "\n\nDelete all nodes with key Test\n";
	std::cout << "Test 1\n";
	DLLExtended list{4, 4, 1, 2, 5, 4, 4, 4};

	list.print();

	std::cout << "Delete all with key 4\n";
	list.delete_all_nodes_with_key(4);

	std::string expected = "1 2 5";
	std::string result = list.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");

	std::cout << "Test 2\n";
	DLLExtended list2{1, 2, 5, 4, 5, 4, 4};

	list2.print();

	std::cout << "Delete all with key 5\n";
	list2.delete_all_nodes_with_key(5);

	expected = "1 2 4 4 4";
	result = list2.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult  : " << result << "\n";
		assert(false);
	}
	list2.debug_print_list("********");
}

int main() {
	delete_all_nodes_with_key_test();
	std::cout << "\n\nNO RTE\n";
	return 0;
}
