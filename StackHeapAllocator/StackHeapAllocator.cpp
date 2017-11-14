/*
  This is a program which allocate data on stack or heap depending on the size of object.
*/

#include <iostream>
#include <type_traits>
#include <string>
#include <array>

template<typename Type>
class Heap {
    Type* ptr;
public:
    Heap() : ptr{ new Type } { std::cout << "Heap" << std::endl; }
    ~Heap() { delete ptr; }
    
    Heap(const Heap&) = delete;
    Heap& operator=(const Heap&) = delete;
    
    Type& operator*() { return *ptr; }
    Type* operator->() { return ptr; }
};

template<typename Type>
class Stack {
    Type val;
public:
    Stack() { std::cout << "Stack" << std::endl; }
    ~Stack() { }
    
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    
    Type& operator*() { return val; }
    Type* operator->() { return &val; }
};

template<typename Type>
struct Object {
    using type = typename std::conditional_t<(sizeof(Type) <= 256), Stack<Type>, Heap<Type>>;
};

template<typename T>
using Holder = typename Object<T>::type;

int main() {
    Holder<double> h1;
    *h1 = 10.4;
    std::cout << *h1 << std::endl;
    
    Holder<std::array<int, 70>> h2;
    for(int i = 0; i < 70; ++i)
        (*h2)[i] = i;
    std::cout << (*h2)[0] << std::endl;
}
