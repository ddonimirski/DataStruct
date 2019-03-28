#include <iostream>
#include <vector>

using std::vector;
using item_t = int64_t;
using seq_t = vector<item_t>;

int lcs3(seq_t const& a, seq_t const& b, seq_t const& c)
{
    auto const sa = a.size();
    auto const sb = b.size();
    auto const sc = c.size();
    int memo[sa+1][sb+1][sc+1];

    for (auto ia = 0u; ia <= sa; ++ia)
    {
        for (auto ib = 0u; ib <= sb; ++ib)
        {
            for (auto ic = 0u; ic <= sc; ++ic)
            {
                if (0 == ia || 0 == ib || 0 == ic)
                {
                    memo[ia][ib][ic] = 0;
                }

                else if (a[ia-1] == b[ib-1] && b[ib-1] == c[ic-1])
                {
                    memo[ia][ib][ic] = 1 + memo[ia-1][ib-1][ic-1];
                }

                else
                {
                    memo[ia][ib][ic] = std::max(std::max(memo[ia-1][ib][ic],memo[ia][ib-1][ic]), memo[ia][ib][ic-1]);
                }
            }
        }
    }

    return memo[sa][sb][sc];
}

int main() {
  size_t an;
  std::cin >> an;
  seq_t a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  seq_t b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  seq_t c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
