#include <iostream>

using ret_t = uint32_t;


ret_t get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    ret_t previous = 1;
    ret_t current  = 1;

    for (int i = 2; i < n; ++i) {
        auto tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}


ret_t get_fibonacci_last_digit_fast(int n) {

    if (n <= 1)
        return n;

    ret_t previous = 1;
    ret_t current  = 1;

    for (int i = 2; i < n; ++i) {
        auto tmp_previous = previous;
        previous = current;
        current += tmp_previous;
        current %= 10;
    }

    return current;
}

#if defined STRESS_TEST
#endif

int main() {
    int n;
    std::cin >> n;
#if defined STRESS_TEST
    auto const c = get_fibonacci_last_digit_naive(n);
    std::cout << c << '\n';
#endif
    auto const c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
    }
