#include <iostream>
#include <vector>
using std::vector;

using type_t = uint64_t;

type_t get_fibonacci_partial_sum_naive(type_t from, type_t to) {
    type_t sum = 0;

    type_t current = 0;
    type_t next  = 1;

    for (type_t i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        type_t new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

type_t fibonacci_fast(type_t n)
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
    }

    return curr;
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

type_t get_pisano_period_length(type_t m)
{
    type_t F1 = 0, F2 = 1, F;
    type_t const m2 = m * m;
    for (type_t i = 0; i < m2; ++i)
    {
        F = (F1 + F2) % m;
        F1 = F2;
        F2 = F;
        if (F1 == 0 && F2 == 1)
            return i + 1;
    }

    return m2; /// never happend
}

type_t fibonacci_huge_fast(type_t n, type_t m) {
    n %= get_pisano_period_length(m);

    return fibonacci_fast(n) % m;
}

type_t fibonacci_partial_sum_fast(type_t from, type_t to) {

    if (from == to) {
        from %= 60;
        return fibonacci_last_digit_fast(from);
    }

    from %= 60;
    to %= 60;

    to  = fibonacci_huge_fast(to + 2, 10) - 1;
    to -= fibonacci_huge_fast(from + 2, 10) - 1;
    to %= 10;
    return to;
}


int main() {
    type_t from, to;
    std::cin >> from >> to;
    std::cout << fibonacci_partial_sum_fast(from, to) << '\n';
}
