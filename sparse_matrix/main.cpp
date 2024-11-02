#include "sparce_matrix.hpp"
#include <iostream>

void test_sparse()
{
	SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	// mat.set_value(1, 70, 1);
	std::cout << "Matrix 1 : \n";
	std::cout << mat << std::endl;
	mat.print_nonzero();

	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	std::cout << "\nMatrix 2 : \n";
	std::cout << mat2 << std::endl;
	mat2.print_nonzero();

	std::cout << "\nMat1 + Mat2 = \n";
	auto matRes = mat + mat2;
	std::cout << matRes << std::endl;
}

int main()
{
	// test_col();
	test_sparse();

	std::cout << "\n\n\nNO RTE\n";

	return 0;
}
