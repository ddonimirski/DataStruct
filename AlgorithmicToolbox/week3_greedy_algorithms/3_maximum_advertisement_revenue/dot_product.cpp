#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::sort;


size_t n;

int64_t max_dot_product(vector<int>& a, vector<int>& b)
{
    sort(begin(a),end(a));
    sort(begin(b),end(b));

    int64_t result = 0;
    for (size_t i = 0; i < n; i++)
    {
        result += static_cast<int64_t>(a[i]) * b[i];
    }
    return result;
}

int main()
{
  std::cin >> n;
  vector<int> a(n), b(n);

  for (size_t i = 0; i < n; i++)
  {
    std::cin >> a[i];
  }

  for (size_t i = 0; i < n; i++)
  {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
