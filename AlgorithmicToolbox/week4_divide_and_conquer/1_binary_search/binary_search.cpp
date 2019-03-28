#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x) {

  int left = 0, right = static_cast<int>(a.size()-1);

  while (left <= right)
  {
      int m = (left + right)/2;

      if (a[m] == x)
          return m;
      else if (a[m] < x)
          left = m + 1;
      else
          right = m - 1;
  }

  return -1;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (auto& v: a)
  {
      std::cin >> v;
  }

  int m;
  std::cin >> m;
  vector<int> b(m);
  for (auto& v: b)
  {
      std::cin >> v;
  }

  for (auto const v: b)
  {
      std::cout << binary_search(a, v) << ' ';
  }

  std::cout << '\n';
}
