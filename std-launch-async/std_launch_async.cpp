/*
  Here is an implementation of std::launch::async.
  Function really_async_result() uses std::result_of<> which was deprecated in C++17.
  Since C++17 we should use std::invoke_result<> as in function really_async_invoke().
  http://en.cppreference.com/w/cpp/types/result_of
  
  Furthermore, since C++14 we can use decltype(auto) declaration instead of writing function returning type as in struct AsyncCallableObject.
  There is a difference between 'auto' and 'decltype(auto)' - using auto means that we remove a reference in template functions.
*/

#include <iostream>
#include <future>
#include <type_traits>
#include <mutex>
std::mutex mut;

void f() {
    std::lock_guard<std::mutex> lg{ mut };
    std::cout << "f()" << std::endl;
}

struct AsyncCallableObject {
    template<typename F, typename... Ts>
    decltype(auto) operator()(F&& f, Ts&&... params) {
        return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
    }
};

template<typename F, typename... Ts>
inline std::future<typename std::result_of<F(Ts...)>::type>
really_async_result(F&& f, Ts&&... params) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}

template<typename F, typename... Ts>
inline std::future<typename std::invoke_result_t<F, Ts...>>
really_async_invoke(F&& f, Ts&&... params) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}

int main() {
    auto f1 = AsyncCallableObject()(f);
    auto f2 = really_async_result(f);
    auto f3 = really_async_invoke(f);

    f1.get();
    f2.get();
    f3.get();
}
