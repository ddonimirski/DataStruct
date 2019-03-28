#include <iostream>
#include <algorithm>
#include <map>

using ret_t = uint64_t;
using count_t = uint32_t;


ret_t lcm_naive(int a, int b) {
  for (long l = 1; l <= (ret_t) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}


ret_t lcm(ret_t a, ret_t b)
{
    std::map<ret_t, count_t> ma, mb;

    auto div = [](auto& m, auto v) {

        ret_t d = 2;

        while(d <= v && v > 1)
        {
            while (0 == v%d)
            {
                v/=d;
                m[d]++;
            }
            ++d;
        }
    };

    div(ma,a);
    div(mb,b);

    ret_t ret = 1;

    for (auto const kva: ma)
    {
        auto vb = mb[kva.first];
        auto n = vb > kva.second ? vb: kva.second;

        while (n--)
        {
            ret *= kva.first;
        }
        mb[kva.first] = 0;
    }

    for (auto kvb: mb)
    {
        while (kvb.second-- && kvb.first)
        {
            ret *= kvb.first;
        }
    }

    return ret;
}


ret_t gcd(ret_t a, ret_t b)
{
    do
    {
        if (a < b)
        {
            auto t = a;
            a = b%a;
            b = t;
        }

        else
        {
            a = a%b;
        }

    }
    while (a);

    return b;
}

ret_t lcm_fast(ret_t a, ret_t b)
{
    auto ret = a;
    ret *= b;
    ret /= gcd(a,b);
    return ret;
}


int main() 
{

    ret_t a,b;
    std::cin >> a >> b;

    std::cout << lcm_fast(a, b) << std::endl;
    return 0;
}
