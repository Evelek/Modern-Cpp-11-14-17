/*
  Member function qualifiers aren't very popular. Their usage is shown below - lines 29 and 33.
*/

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

class Person {
	std::string name;
	std::string surname;
	std::vector<int> favourite_numbers;
public:
	Person(std::string&& name, std::string&& surname, std::initializer_list<int> favourite_numbers)
		: name{ std::move(name) }, surname{ std::move(surname) } {
		for (size_t i = 0; i < favourite_numbers.size(); ++i)
			this->favourite_numbers.push_back(favourite_numbers.begin()[i]);
	}

	void show() const {
		std::cout << "Name: " << name << ", surname: " << surname << std::endl;
		std::cout << "Favourite numbers: ";
		for (int elem : favourite_numbers)
			std::cout << elem << ' ';
		std::cout << std::endl;
	}

	std::vector<int>& get_favourites() & {
		std::cout << "Calling get_favourites() &" << std::endl;
		return favourite_numbers;
	}
	std::vector<int> get_favourites() && {
		std::cout << "Calling get_favourites() &&" << std::endl;
		return std::move(favourite_numbers);
	}
};

Person make_person(std::string&& name, std::string&& surname, std::initializer_list<int> favourite_numbers) {
	return Person{ std::forward<std::string>(name), std::forward<std::string>(surname), favourite_numbers };
}

int main() {
	Person Majkel = make_person("Majkel", "Evelek", { 6, 7, 9, 21, 22 });
	Majkel.show();
	auto Majkel_numbers = Majkel.get_favourites();

	std::cout << std::endl;

	std::vector<int> John_numbers = make_person("John", "Smith", { 1, 2, 11, 12 }).get_favourites();
	std::cout << "Favourite numbers: ";
	for (int elem : John_numbers)
		std::cout << elem << ' ';

	std::cin.get();
}
