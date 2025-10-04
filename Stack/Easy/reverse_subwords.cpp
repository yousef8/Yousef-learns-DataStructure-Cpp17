#include "stack_array.hpp"
#include <cassert>
#include <string>

std::string reverse_subwords(std::string line)
{
	Stack stack{static_cast<int>(line.length())};
	std::string reversed_string = "";

	for (char &ch : line)
	{
		if (ch != ' ')
		{
			stack.push(ch);
		}
		else
		{
			while (!stack.isEmpty())
			{
				reversed_string += stack.pop();
			}
			reversed_string += " ";
		}
	}

	while (!stack.isEmpty())
	{
		reversed_string += stack.pop();
	}

	return reversed_string;
}

int main()
{
	assert(reverse_subwords("abc d efg xy") == "cba d gfe yx");
	std::cout << "All tests ran successfully\n";
	return 0;
}
