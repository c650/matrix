#include <iostream>
#include "./matrix.hpp"

int main() {
	Matrix<int> m1 (3,3);
	std::cin >> m1;

	std::cout << m1.determinant() << '\n';

	return 0;
}
