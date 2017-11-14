#include <iostream>
#include <functional>
#include <thread>
#include <vector>

class ThreadGuard {
    std::thread& t;
public:
    explicit ThreadGuard(std::thread& t) : t(t) { }
    ~ThreadGuard() {
        if(t.joinable())
            t.join();
    }
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

struct EvenOddNumber {
    bool operator()(int val) {
        return val % 2 == 0;
    }
};

void calculate(std::function<bool(int)>& fun, std::vector<int>& vec_even_number, std::vector<int>& vec_odd_number) {
    std::thread t(
        [&fun, &vec_even_number, &vec_odd_number] {
            for(int i = 0; i < 10; ++i) {
                if(fun(i))
                    vec_even_number.push_back(i);
                else
                    vec_odd_number.push_back(i);
            }
        }
    );
    ThreadGuard tg(t);
}

int main() {
    std::vector<int> vec_even_number;
    std::vector<int> vec_odd_number;
    std::function<bool(int)> fun = EvenOddNumber();
    
    {
        std::thread t(calculate, std::ref(fun), std::ref(vec_even_number), std::ref(vec_odd_number));
        ThreadGuard tg(t);
    }
    
    for(int elem : vec_even_number)
        std::cout << elem << ' ';
    std::cout << std::endl;
        
    for(int elem : vec_odd_number)
        std::cout << elem << ' ';
}
