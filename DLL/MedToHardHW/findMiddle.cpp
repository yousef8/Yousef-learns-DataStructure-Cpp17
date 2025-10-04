#include "../include/dll.hpp"

class DllExtended : public Dll {
  public:
	DllExtended() = default;

	DllExtended(const std::initializer_list<int> &lst) : Dll{lst} {}

	int getMiddleVal() {
		auto front = head.get();
		auto back = tail;

		while (front != back && front->prev != back) {
			front = front->next.get();
			back = back->prev;
		}

		debug_verify_data_integrity();
		return front->data;
	}

	int getMiddleValWithRabbitAndHair() {
		auto rabbit = head.get();
		auto hair = head.get();

		while (rabbit && rabbit->next) {
			rabbit = rabbit->next->next.get();
			hair = hair->next.get();
		}

		return hair->data;
	}
};

int main() {
	std::cout << "######################################\n";
	std::cout << "####Using DllExtended prev & next Pointers####\n";
	std::cout << "######################################\n";

	DllExtended evenDll{1, 2, 3, 4, 5, 6};

	std::cout << evenDll << "\n";
	std::cout << "Middle value is : " << evenDll.getMiddleVal() << "\n";

	DllExtended oddDll{1, 2, 3, 4, 5};
	std::cout << oddDll << "\n";
	std::cout << "Middle value is : " << oddDll.getMiddleVal() << "\n";

	std::cout << "\n######################################\n";
	std::cout << "####Using Rabbit & Hair Algo####\n";
	std::cout << "######################################\n";
	std::cout << evenDll << "\n";
	std::cout << "Middle value is : " << evenDll.getMiddleValWithRabbitAndHair()
			  << "\n";

	std::cout << oddDll << "\n";
	std::cout << "Middle value is : " << oddDll.getMiddleValWithRabbitAndHair()
			  << "\n";

	DllExtended singleElemDll{1};
	std::cout << singleElemDll << "\n";
	std::cout << "Middle value is : "
			  << singleElemDll.getMiddleValWithRabbitAndHair() << "\n";
	return 0;
}
