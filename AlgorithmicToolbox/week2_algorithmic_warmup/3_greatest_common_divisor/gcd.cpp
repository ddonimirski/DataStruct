#include <iostream>

using ret_t = uint64_t;

ret_t gcd_naive(ret_t a, ret_t b) {
  ret_t current_gcd = 1;
  for (ret_t d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
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

    }
    while (a);

    return b;
}


int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}
