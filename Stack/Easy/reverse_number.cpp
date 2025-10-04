#include "stack_array.hpp"
#include <cassert>
#include <string>

int reverse_number(int num)
{
	Stack stack{20};
	int reversed_num = 0;
	while (num)
	{
		stack.push(num % 10);
		num /= 10;
	}

	int tens = 1;
	while (!stack.isEmpty())
	{
		reversed_num = (stack.pop() * tens) + reversed_num;
		tens *= 10;
	}

	return reversed_num;
}

int main()
{
	assert(reverse_number(1234) == 4321);
	std::cout << reverse_number(1234) << std::endl;
	std::cout << reverse_number(0) << std::endl;
	std::cout << reverse_number(-1234) << std::endl;
	std::cout << "All tests ran successfully\n";
	return 0;
}
