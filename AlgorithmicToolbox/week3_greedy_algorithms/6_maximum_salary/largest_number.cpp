#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::sort;


string largest_number(vector<string>& a)
{

    sort(a.begin(), a.end(), [](string const& l, string const& r)
            {
                auto const lr = l+r;
                auto const rl = r +l;
                auto const s = lr.size();

                for (size_t i = 0; i < s; ++i)
                {
                    if (lr[i] == rl[i]) continue;

                    return lr[i] > rl[i];
                }

                return false;
            });

    std::stringstream ret;
    for (auto const& v: a)
        ret << v;

    string result;
    ret >> result;
    return result;
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<string> a(n);


  for (size_t i = 0; i < n; i++)
    std::cin >> a[i];

  std::cout << largest_number(a);
}
