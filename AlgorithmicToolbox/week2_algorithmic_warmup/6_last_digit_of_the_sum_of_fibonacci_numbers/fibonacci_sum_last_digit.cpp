#include <iostream>

using type_t = uint64_t;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}


unsigned fibonacci_last_digit_fast(type_t n)
{
    if (n <= 1u)
    {
        return n;
    }

    type_t curr = 1u;
    type_t prev = 1u;

    for (type_t i = 2u; i < n; ++i)
    {
        auto const tmp = prev;
        prev = curr;
        curr += tmp;
        curr %= 10;
    }

    return curr % 10u;
}

int fibonacci_sum_last_digit_fast(type_t n)
{
    auto const new_last = fibonacci_last_digit_fast((n + 2) % 60);
    if (new_last == 0) {
        return 9;
    } else {
        return new_last - 1;
    }
}

int main() {
    type_t n;
    std::cin >> n;
    std::cout << fibonacci_sum_last_digit_fast(n);
}
