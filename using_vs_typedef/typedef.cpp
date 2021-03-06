/*
  When we use 'typedef' in templates we have to add word 'typename' before name of dependent type as in lines 27 and 28.
*/

#include <iostream>
#include <set>
#include <initializer_list>
#include <functional>
#include <typeinfo>

template<typename Type>
struct SET_GREATER {
	typedef std::set<Type, std::greater<Type>> type;
};

template<typename Type>
struct SET_LESS {
	typedef std::set<Type, std::less<Type>> type;
};

template<typename Type>
class Numbers {
public:
	enum sort_mode { less, great };
private:
	sort_mode mode;
	typename SET_GREATER<Type>::type set_greater;
	typename SET_LESS<Type>::type set_less;
public:
	Numbers(sort_mode mode, std::initializer_list<Type> lista) : mode(mode) {
		if (mode == less) {
			for (auto pos = lista.begin(); pos != lista.end(); ++pos)
				set_less.insert(*pos);
		}
		else {
			for (auto pos = lista.begin(); pos != lista.end(); ++pos)
				set_greater.insert(*pos);
		}
	}
	~Numbers() {
		if (set_less.size())
			set_less.clear();
		if (set_greater.size())
			set_greater.clear();
	}

	void show() {
		if (set_less.size()) {
			std::cout << "vec type: " << typeid(set_less).name() << "\n" << std::flush;
			for (int elem : set_less)
				std::cout << elem << ' ';
			std::cout << std::endl;
		}
		if (set_greater.size()) {
			std::cout << "vec_type: " << typeid(set_greater).name() << "\n" << std::flush;
			for (const auto &elem : set_greater)
				std::cout << elem << ' ';
			std::cout << std::endl;
		}
	}
};

int main() {
	Numbers<int> first{ Numbers<int>::great,{ 1, 2, 3, 4, 5 } };
	first.show();

	Numbers<double> second{ Numbers<double>::less,{ 1.1, 2.2, 3.3, 4.4, 5.5 } };
	second.show();

	std::cin.get();
}
