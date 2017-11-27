/*
  Every STL container has its own way for removing elements.
  The idea for distinguiring std::set<> and std::list<> by using std::true_type and std::false_type was from:
  https://dsp.krzaq.cc/post/477/zwi-1-jak-wykryc-kontenery-asocjacyjne-w-czasie-kompilacji/
*/

/*
Every STL container has its own way for removing elements.
The idea for distinguiring std::set<> and std::list<> by using std::true_type and std::false_type was from:
https://dsp.krzaq.cc/post/477/zwi-1-jak-wykryc-kontenery-asocjacyjne-w-czasie-kompilacji/
*/

#include <iostream>
#include <algorithm>
#include <type_traits>
#include <iterator>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>

template<typename Type>
struct is_special : std::false_type {};

template<typename... Type>
struct is_special<std::set<Type...>> : std::true_type {};

template<typename Type>
void delete_foo(Type& coll, typename std::remove_reference_t<Type>::value_type val, std::random_access_iterator_tag, std::false_type) {
	std::cout << "random access iterator tag for vector and deque" << std::endl;
	coll.erase(std::remove(coll.begin(), coll.end(), val), coll.end());
}

template<typename Type>
void delete_foo(Type& coll, typename std::remove_reference_t<Type>::value_type val, std::bidirectional_iterator_tag, std::false_type) {
	std::cout << "bidirectional iterator tag for list" << std::endl;
	coll.remove(val);
}

template<typename Type>
void delete_foo(Type& coll, typename std::remove_reference_t<Type>::key_type val, std::bidirectional_iterator_tag, std::true_type) {
	std::cout << "bidirectional iterator tag for set" << std::endl;
	coll.erase(val);
}

template<typename Type>
void delete_foo(Type& coll, typename std::remove_reference_t<Type>::value_type val, std::forward_iterator_tag, std::false_type) {
	std::cout << "forward iterator tag for forward_list" << std::endl;
	coll.remove(val);
}

template<typename Type>
void deleter(Type&& coll, typename std::remove_reference_t<Type>::value_type val) {
	using Iter = typename std::remove_reference_t<Type>::iterator;
	using decayed = typename std::decay_t<Type>;
	using is_special = is_special<decayed>;
	delete_foo(std::forward<Type>(coll), val, typename std::iterator_traits<Iter>::iterator_category{}, is_special{});
}

template<typename Type>
struct PrintContainer {
	void operator()(Type val) const {
		std::cout << val << ' ';
	}
};

int main() {
	std::vector<int> vec{ 1, 2, 3, 2, 4 };
	deleter(vec, 2);
	std::for_each(vec.begin(), vec.end(), PrintContainer<int>());
	std::cout << std::endl;

	std::deque<int> deq{ 1, 2, 3, 2, 4 };
	deleter(deq, 2);
	std::for_each(deq.cbegin(), deq.cend(), PrintContainer<int>());
	std::cout << std::endl;

	std::list<int> lista{ 1, 2, 3, 2, 4 };
	deleter(lista, 2);
	std::for_each(lista.cbegin(), lista.cend(), PrintContainer<int>());
	std::cout << std::endl;

	std::forward_list<int> forward_lista{ 1, 2, 3, 2, 4 };
	deleter(forward_lista, 2);
	std::for_each(forward_lista.cbegin(), forward_lista.cend(), PrintContainer<int>());
	std::cout << std::endl;

	std::set<int> sett{ 1, 2, 3, 2, 4 };
	deleter(sett, 2);
	std::for_each(sett.cbegin(), sett.cend(), PrintContainer<int>());
	std::cout << std::endl;
}
