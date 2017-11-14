/*
  Here is an implementation of std::launch::async.
  Function really_async_result() uses std::result_of<> which was deprecated in C++17.
  Since C++17 we should use std::invoke_result<> as in function really_async_invoke().
  http://en.cppreference.com/w/cpp/types/result_of
*/

#include <iostream>
#include <future>
#include <type_traits>

void f() {
    std::cout << "f()" << std::endl;
}

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
    auto f1 = really_async_result(f);
    auto f2 = really_async_invoke(f);

    f1.get();
    f2.get();
}
