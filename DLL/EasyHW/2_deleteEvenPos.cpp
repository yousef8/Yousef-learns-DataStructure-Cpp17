#include "../include/dll.hpp"
#include <initializer_list>

class DLLExt : public Dll {
  public:
	DLLExt() = default;

	DLLExt(const std::initializer_list<int> &lst) : Dll(lst) {}

	DLLExt(const DLLExt &another) = delete;
	DLLExt &operator=(const DLLExt &another) = delete;

	void delete_even_pos() {
		for (Node *cur{head->next.get()}; cur;) {
			Node *to_be_deleted = cur;

			if ((cur = cur->next.get()))
				cur = cur->next.get();

			delete_a_node(to_be_deleted);
		}
	}
};

void Delete_even_pos_test() {
	std::cout << "\n\nDelete Even Position Test\n";
	DLLExt list{1, 2, 3, 4, 10};

	list.print();
	std::string expected = "1 3 10";

	list.delete_even_pos();
	std::string result = list.debug_to_string();
	if (expected != result) {
		std::cout << "no match:\nExpected: " << expected
				  << "\nResult  : " << result << "\n";
		assert(false);
	}
	list.debug_print_list("********");
}

int main() {
	Delete_even_pos_test();

	std::cout << "\nNO RTE\n";
	return 0;
}
