#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>

using std::vector;
using std::swap;


#define DPR(v) std::cout << "D> " << v << std::endl

template<class T>
void pr(T& c)
{
    for (auto const v: c)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;
}

template<class T>
void pr(T& c, int l, int r)
{
    std::cout << l << ", " << r << '\n';
    while (l <= r)
    {
        std::cout << c[l++] << ' ';
    }
    std::cout << std::endl;
}


template<class T, bool random_pivot = true>
auto partition2(vector<T> &a, int l, int r)
{
    if constexpr (random_pivot) {
        int const p = (rand() % (r-l+1)) + l;
        swap(a[p], a[l]);
    }

    auto const p = a[l];

    for (int i = l + 1; i <= r; )
    {
        if (a[i] == p)
            ++i;
        else if (a[i] > p)
            swap(a[i], a[r--]);
        else
            swap(a[i++], a[l++]);
    }


    return std::make_tuple(l,r);
}

template<class T>
void randomized_quick_sort(vector<T> &a, int l, int r)
{
  if (l >= r)
  {
    return;
  }

  auto const [ml, mr] = partition2(a, l , r);

  randomized_quick_sort(a, l, ml - 1);
  randomized_quick_sort(a, mr + 1, r);
}


int main()
{
  int n;
  std::cin >> n;
  vector<uint64_t> a(n);
  for (size_t i = 0; i < a.size(); ++i)
  {
    std::cin >> a[i];
  }

  randomized_quick_sort(a, 0, a.size() - 1);

  pr(a);
}
