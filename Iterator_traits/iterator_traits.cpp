/*
  Sorting function is selected depending on iterator category each STL container.
  Sorting::operator() is called with std::invoke added in C++17.
*/

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <type_traits>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>

struct Sorting {
	template<typename Type>
	void operator()(Type& coll) {
		using Iter = typename Type::iterator;
		sort_function(coll, typename std::iterator_traits<Iter>::iterator_category{});
	}
private:
	template<typename Random>
	void sort_function(Random& coll, std::random_access_iterator_tag) {
		auto t1 = std::chrono::high_resolution_clock::now();
		std::sort(coll.begin(), coll.end());
		auto t2 = std::chrono::high_resolution_clock::now();
		std::cout << "Sorted in: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << std::endl;
	}

	template<typename Bidirection>
	void sort_function(Bidirection& coll, std::bidirectional_iterator_tag) {
		auto t1 = std::chrono::high_resolution_clock::now();
		coll.sort();
		auto t2 = std::chrono::high_resolution_clock::now();
		std::cout << "Sorted in: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << std::endl;
	}
};

int main() {
	std::vector<int> vec;

	for (int i = 0; i < 100000; ++i)
		vec.push_back(i);

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vec.begin(), vec.end(), g);

	std::list<int> lista{ vec.begin(), vec.end() };

	std::invoke(Sorting(), vec);
	std::invoke(Sorting(), lista);

	std::cin.get();
}
