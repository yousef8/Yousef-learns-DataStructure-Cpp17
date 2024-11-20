#include "stack_array.hpp"
#include <cassert>
#include <iostream>

bool is_right(int num) { return num > 0; }
bool is_left(int num) { return num < 0; }
bool is_collision(int right_astrid, int left_astrid) {
	return is_right(right_astrid) && is_left(left_astrid);
}
int collide(int right, int left) {
	if (right + left == 0) {
		return 0;
	}
	return abs(right) > abs(left) ? right : left;
}

int *asteroidCollision(const int *asteroids, int size, int &resultSize) {
	Stack stk{size};
	for (int i{size - 1}; i >= 0; --i) {
		int right_astrid = asteroids[i];

		while (!stk.isEmpty() && is_collision(right_astrid, stk.peek())) {
			right_astrid = collide(right_astrid, stk.pop());
		}

		if (right_astrid) {
			stk.push(right_astrid);
		}
	}
	resultSize = stk.capacity();
	int *surviving_astrids = new int[resultSize];
	int count{0};
	while (!stk.isEmpty()) {
		surviving_astrids[count++] = stk.pop();
	}

	return surviving_astrids;
}

void runTests() {
	int asteroids1[] = {1, 2, 3, 4};
	int expected1[] = {1, 2, 3, 4};
	int resultSize1;
	int *result1 = asteroidCollision(asteroids1, 4, resultSize1);
	assert(resultSize1 == 4);
	for (int i = 0; i < resultSize1; ++i)
		assert(result1[i] == expected1[i]);
	delete[] result1;

	int asteroids2[] = {-1, -2, -3, -4};
	int expected2[] = {-1, -2, -3, -4};
	int resultSize2;
	int *result2 = asteroidCollision(asteroids2, 4, resultSize2);
	assert(resultSize2 == 4);
	for (int i = 0; i < resultSize2; ++i)
		assert(result2[i] == expected2[i]);
	delete[] result2;

	int asteroids3[] = {-2, -2, 1, 1};
	int expected3[] = {-2, -2, 1, 1};
	int resultSize3;
	int *result3 = asteroidCollision(asteroids3, 4, resultSize3);
	assert(resultSize3 == 4);
	for (int i = 0; i < resultSize3; ++i)
		assert(result3[i] == expected3[i]);
	delete[] result3;

	int asteroids4[] = {-2, 1, -2, 1};
	int expected4[] = {-2, -2, 1};
	int resultSize4;
	int *result4 = asteroidCollision(asteroids4, 4, resultSize4);
	assert(resultSize4 == 3);
	for (int i = 0; i < resultSize4; ++i)
		assert(result4[i] == expected4[i]);
	delete[] result4;

	int asteroids5[] = {5, 4, -3, -6, 2, -3, 6};
	int expected5[] = {-6, -3, 6};
	int resultSize5;
	int *result5 = asteroidCollision(asteroids5, 7, resultSize5);
	assert(resultSize5 == 3);
	for (int i = 0; i < resultSize5; ++i)
		assert(result5[i] == expected5[i]);
	delete[] result5;
}

int main() {
	runTests();
	std::cout << "All tests passed!" << std::endl;
	return 0;
}
