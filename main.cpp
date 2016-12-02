#include <iostream>
#include "./matrix.hpp"

int main() {
	Matrix<int> m1 (3,3), m2 (3,3);
	std::cin >> m1 >> m2;

	std::cout << m1 * m2 << m1 + m2 << m1 - m2 << m1.power(2)
	<< m1 * 3 << std::endl;
	return 0;
}
