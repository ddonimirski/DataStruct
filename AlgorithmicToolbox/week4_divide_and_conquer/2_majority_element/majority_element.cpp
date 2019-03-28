#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

auto count(vector<int>& a, int left, int right, int value)
{
    auto const s2 = (right-left)/2;
    unsigned c = 0;
    for (int i = left; i < right; ++i)
    {
        if (a[i] == value)
        {
            ++c;
        }

        if (c > s2)
        {
            return true;
        }
    }

    return false;
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];


  auto mid = (left+right)/2;
  auto const left_elem = get_majority_element(a, left, mid);

  if (-1 != left_elem && count(a, left, right, left_elem)) return left_elem;

  auto const right_elem = get_majority_element(a, mid, right);

  if (-1 != right_elem && count(a, left, right, right_elem)) return right_elem;

  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
