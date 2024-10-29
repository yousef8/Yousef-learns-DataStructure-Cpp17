#include "sparce_matrix.hpp"
#include <iostream>

int main()
{
	SparceMatrix mat(10, 10);
	// mat.set_value(5, 3, 5);
	// mat.set_value(7, 3, 7);
	// mat.set_value(2, 3, 2);
	// mat.set_value(0, 3, 2);
	// mat.set_value(6, 5, 6);
	// mat.set_value(4, 5, 4);
	// mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	std::cout << mat << std::endl;
	return 0;
}
