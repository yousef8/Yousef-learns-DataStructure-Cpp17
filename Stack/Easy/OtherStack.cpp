#include <cassert>
#include <iostream>
using namespace std;

class OtherStack {
  private:
	int size{};
	int added_elements{};
	int *array{};

	bool shift_right() {
		if (isFull()) {
			return false;
		}

		for (int i{added_elements}; i > 0; --i) {
			array[i] = array[i - 1];
		}
		return true;
	}

	bool shift_left() {
		if (isEmpty()) {
			return false;
		}

		for (int i{0}; i < added_elements - 1; ++i) {
			array[i] = array[i + 1];
		}
		return true;
	}

  public:
	OtherStack(int size) : size(size) { array = new int[size]; }

	~OtherStack() { delete[] array; }

	bool push(int x) // time complexity O(n)
	{
		if (isFull()) {
			return false;
		}
		if (!shift_right()) {
			return false;
		}
		array[0] = x;
		++added_elements;
		return true;
	}

	bool pop() // time complexity O(n) where n is the size of the array
	{
		if (isEmpty()) {
			return false;
		}
		if (!shift_left()) {
			return false;
		}
		--added_elements;
		return true;
	}

	bool peek() {
		if (isEmpty()) {
			return false;
		}
		return true;
	}

	int isFull() { return added_elements == size; }

	int isEmpty() { return added_elements <= 0; }

	void display() {
		for (int i{0}; i < added_elements; ++i)
			cout << array[i] << " ";
		cout << "\n";
	}
};

int main() {

	OtherStack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);

	if (!stk.isFull())
		stk.push(50);
	else
		cout << "Full Stack\n";
	stk.display();				// 30 20 10
	cout << stk.peek() << "\n"; // 30

	while (!stk.isEmpty()) {
		cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10

	return 0;
}
