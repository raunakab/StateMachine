#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "./../src/Iterators.cpp"



int const size_a = 0;
int const size_b = 1;
int const size_c = 10;
std::vector<int> * const list_a = new std::vector<int>();
std::vector<float> * const list_b = new std::vector<float>();
std::vector<int> * const list_c = new std::vector<int>();



bool const isEven(int const & x) { return !(x % 2); }
void add(int & a, int const & b) { a = a + b; return; }
bool * const modulo(int const & x) { if (isEven(x)) return new bool(false); return new bool(true); }
template<class T> void print(T const & x) { std::cout << x << " "; return; }



template<class T> void print_title_and_testlist(std::string const & title, std::vector<T> const & list) {
	print<std::string>(title);
	Iterators<T>::apply(list,print<T>);
	print<std::string>("\n");

	return;
}
template<class T> void print_title_and_test(std::string const & title, T const & test_result) {
	print<std::string>(title);
	print<T>(test_result);
	print<std::string>("\n");

	return;
}



template<class T> void setup_list(std::vector<T> & list, int const size) {
	srand(time(NULL));

	for (int i=0; i<size; i++) {
		T const x = (rand() % 10);
		list.push_back(x);
	}

	return;
}
void setup_test_variables() {
	setup_list<int>(*list_a,size_a);
	setup_list<float>(*list_b,size_b);
	setup_list<int>(*list_c,size_c);
	print_title_and_testlist("List A: ",*list_a);
	print_title_and_testlist("List B: ",*list_b);
	print_title_and_testlist("List C: ",*list_c);

	return;
}



void test_contains(int const x) {
	bool const test_a = Iterators<int>::contains(*list_a,x);
	bool const test_b = Iterators<float>::contains(*list_b,x);
	bool const test_c = Iterators<int>::contains(*list_c,x);

	std::string title_a;
	std::string title_b;
	std::string title_c;

	print_title_and_test("Contains:\tTest A = ",test_a);
	print_title_and_test("Contains:\tTest B = ",test_b);
	print_title_and_test("Contains:\tTest C = ",test_c);

	return;
}

int main() {
	// setup_test_variables();

	std::vector<int> test;
	for (int i=0; i<7; i++) test.push_back(i);
	// for (int i=0; i<20; ++i) test.push_back(5);
	// for (int i=0; i<20; ++i) {
	// 	test.push_back(i);
	// 	test.push_back(5);
	// 	test.push_back((i % 7));
	// 	test.push_back((i % 3));
	// }
	// for (int i=0; i<5; ++i) {
	// 	test.push_back(i);
	// 	test.push_back(5);
	// }



	typename std::vector<int>::iterator itr_0(test.begin());
	typename std::vector<int>::iterator itr_1(test.begin());
	++itr_1;
	++itr_1;
	++itr_1;

	print_title_and_testlist("Test: ", test);
	std::remove(itr_0,itr_1,0);
	// Iterators<int>::remove(test,5);
	// printf("Size of Test:\t%d\n",test.size()); 
	print_title_and_testlist("Test: ", test);
	// bool const residue = Iterators<int>::contains(test,5);
	// std::cout << residue << std::endl;


	// print_title_and_testlist("Reverse Iterator Test List: ", test);

	// std::vector<int>::reverse_iterator r_itr(test.rbegin());
	// std::advance(r_itr, 3);

	// print_title_and_testlist("t = 0:\t", test);
	// Iterators<int>::insert(test,9,6);
	// print_title_and_testlist("t = 1:\t", test);

	// int const selected_00 = *r_itr;
	// int const selected_01 = *r_itr.base();
	// std::cout << "Reverse Iterator Selected Element: " << selected_00 << std::endl;
	// std::cout << "Reverse Base Iterator Selected Element: " << selected_01 << std::endl;

	// test.erase(--(r_itr.base()));
	// print_title_and_testlist("t = 1:\t", test);

	// int const selected_10 = *r_itr;
	// int const selected_11 = *r_itr.base();
	// std::cout << "Reverse Iterator Selected Element (post-addition): " << selected_10 << std::endl;
	// std::cout << "Reverse Base Iterator Selected Element (post-addition): " << selected_11 << std::endl;

	// test.insert(r_itr.base(), 4);
	// print_title_and_testlist("t = 2:\t", test);

	// int const selected_20 = *r_itr;
	// int const selected_21 = *r_itr.base();
	// std::cout << "Reverse Iterator Selected Element (post-deletion): " << selected_20 << std::endl;
	// std::cout << "Reverse Base Iterator Selected Element (post-deletion): " << selected_21 << std::endl;

	// print_title_and_testlist("t = 3:\t", test);

	// test_contains(5);

	// bool                       const comparator_test = Iterators<int>::comparator (*x, nullptr);
	// bool                       const ormap_test      = Iterators<int>::ormap      (*x, isEven);
	// bool                       const andmap_test     = Iterators<int>::andmap     (*x, isEven);
	// std::vector<int const *> * const filter_test     = Iterators<int>::filter     (*x, isEven);
	// std::vector<int *>       * const newFilter_test  = Iterators<int>::newFilter  (*x, isEven);
	// std::vector<bool *>      * const map_test        = Iterators<int>::map        (*x, modulo);
	// int                      * const accumulate_test = Iterators<int>::accumulate (*x, add);

	// std::vector<int const> * const filter_test_drf    = Iterators<int const>:: dereference (*filter_test);
	// std::vector<int>       * const newFilter_test_drf = Iterators<int>::       dereference (*newFilter_test);
	// std::vector<bool>      * const map_test_drf       = Iterators<bool>::      dereference (*map_test);



	// print<std::string>("x (vals): ");
	// Iterators<int>::apply(*x,print<int>);
	// print<std::string>("\n");

	// print<std::string>("Contains: ");
	// print<bool>(contains_test);
	// print<std::string>("\n");

	// print<std::string>("Comparator: ");
	// print<bool>(comparator_test);
	// print<std::string>("\n");

	// print<std::string>("Or Map: ");
	// print<bool>(ormap_test);
	// print<std::string>("\n");

	// print<std::string>("And Map: ");
	// print<bool>(andmap_test);
	// print<std::string>("\n");

	// print<std::string>("Filter (drf): ");
	// Iterators<int const>::apply(*filter_test_drf,print<int const>);
	// print<std::string>("\n");

	// print<std::string>("New Filter (drf): ");
	// Iterators<int>::apply(*newFilter_test_drf,print<int>);
	// print<std::string>("\n");

	// print<std::string>("Map (drf): ");
	// Iterators<bool>::apply(*map_test_drf,print<bool>);
	// print<std::string>("\n");

	// print<std::string>("Accumulate: ");
	// print<int>(*accumulate_test);
	// print<std::string>("\n");

	return 0;
}
