#include <iostream>
#include <vector>
#include <algorithm>

using ret_t = uint64_t;

ret_t get_fibonacci_huge_naive(uint64_t n, uint64_t m) {
    if (n <= 1)
        return n;

    uint64_t previous = 0;
    uint64_t current  = 1;

    for (uint64_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current += tmp_previous;
    }

    return current % m;
}


size_t get_pisano_period(ret_t m, std::vector<ret_t>& v)
{
    while (true)
    {
        auto t = (v[v.size() - 1] + v[v.size() - 2]) % m;

        v.push_back(t);

        if (t == 0
            && v.size() % 2 == 0
            && std::equal(v.begin(), v.begin() + v.size() / 2, v.begin() + v.size() / 2, v.end()))
        {
            break;
        }
    }
    return v.size() / 2;
}


ret_t get_fibonacci_huge_fast(ret_t n, ret_t m)
{
    std::vector<ret_t> v{1, 1};

    auto const pp = get_pisano_period(m,v);

    auto const nn = n%pp;

#if  0
    std::cout << "[" << n << ", "  << m << "] " << pp <<"(" << v.size() << ") " << nn << "\n";
    for (auto const vv : v)
    {
        std::cout << vv << " ";
    }
    std::cout << "\n";
#endif

    if (nn)
    {
        return v[nn-1u];
    }

    return 0;
}

int main()
{
    uint64_t n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
