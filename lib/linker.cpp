#include "./Iterators/src/Iterators.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>



template<class T> void print(T const & t) {
	std::cout << t << "\n";
	return;
}

int main() {
	std::vector<int> a(16,4);
	Iterators<int>::apply(a,print<int>);

	return 0;
}
