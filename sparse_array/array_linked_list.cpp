#include "array_linked_list.hpp"
#include <iostream>

int main()
{
	ArrayLinkedList<int> array{10};
	array.set_value(50, 5);
	array.set_value(20, 2);
	array.set_value(70, 7);
	array.set_value(40, 4);
	std::cout << "Array 1 : ";
	array.print_array_nonzero();

	ArrayLinkedList<int> arr2(10);
	arr2.set_value(1, 4);
	arr2.set_value(3, 7);
	arr2.set_value(4, 6);
	std::cout << "Array 2 : ";
	arr2.print_array_nonzero();

	ArrayLinkedList<ArrayLinkedList<int>> mat1{};
	mat1.set_value(array, 1);
	std::cout << "Matrix 1 : ";
	mat1.print_array_nonzero();

	ArrayLinkedList<ArrayLinkedList<int>> mat2{};
	mat2.set_value(arr2, 1);
	std::cout << "Matrix 2 : ";
	mat2.print_array_nonzero();

	std::cout << "mat1 + mat2 = ";
	auto resMat = mat1 + mat2;
	resMat.print_array_nonzero();

	std::cout << "Matrix 1 : ";
	mat1.print_array_nonzero();

	std::cout << "Matrix 2 : ";
	mat2.print_array_nonzero();
	return 0;
}
