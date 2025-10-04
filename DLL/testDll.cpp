#include "./include/dll.hpp"

void insert_sorted_test() {
	std::cout << "\n\nInsert Sorted Test\n";
	Dll list;

	list.insert_end(3);
	list.insert_end(5);
	list.insert_end(7);
	list.insert_sorted(2);
	list.insert_sorted(9);
	list.insert_sorted(7);
	list.insert_sorted(4);
	list.insert_sorted(1);

	list.print();
	// list.print_reversed();

	std::string expected = "1 2 3 4 5 7 7 9";
	std::string result = list.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

void deletion_test() {
	std::cout << "\n\nDeletion Test\n";
	Dll list;

	list.insert_end(3);
	list.insert_end(5);
	list.insert_end(7);
	list.insert_front(7);
	list.delete_front();
	list.delete_end();
	list.insert_sorted(2);
	list.insert_sorted(9);
	list.insert_sorted(7);
	list.insert_sorted(4);
	list.insert_sorted(1);
	list.delete_node_with_key(9);

	list.print();
	list.print_reversed();

	std::string expected = "1 2 3 4 5 7";
	std::string result = list.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

int main() {
	insert_sorted_test();
	deletion_test();

	std::cout << "\n\nNO RTE\n";
	return 0;
}
