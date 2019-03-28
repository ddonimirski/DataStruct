#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::set;
using ret_t = uint64_t;


template<class T>
ret_t _merge(std::vector<T>& arr, std::vector<T>& temp, ret_t left, ret_t mid, ret_t right)
{
    int inv_count = 0;
    auto i = left;
    auto j = mid;
    auto k = left;

    while (i <= mid-1 && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];

            inv_count += (mid - i);
        }
    }

    while(i <= mid-1)
        temp[k++] = arr[i++];

    while(j <= right)
        temp[k++] = arr[j++];

    for (i=left; i<=right; ++i)
        arr[i] = temp[i];

    return inv_count;
}

template<class T>
ret_t _merge_sort(std::vector<T>& arr, std::vector<T>& temp, ret_t left, ret_t right)
{
    ret_t inv_count = 0;

    if (right > left)
    {
        auto mid = (right+left)/2;
        inv_count = _merge_sort(arr, temp, left, mid);
        inv_count += _merge_sort(arr, temp, mid+1, right);

        inv_count += _merge(arr, temp, left, mid+1, right);
    }

    return inv_count;
}

template<class T>
ret_t get_number_of_inversions(vector<T>& arr)
{
    vector<T> temp(arr.size());
    return _merge_sort(arr, temp, 0, arr.size()-1);
}


template<class T>
ret_t get_number_of_inversion_naive(vector<T>& arr)
{
    auto const size = arr.size();
    ret_t inv_count = 0;

    for (ret_t i = 0; i<size-1; ++i)
    {
        for (ret_t j = i+1; j<size; ++j)
        {
            if (arr[i]>arr[j])
            {
                ++inv_count;
            }
        }
    }
    return inv_count;
}


template<class T>
ret_t get_number_of_inversions_by_set(vector<T> const& a)
{
    ret_t number_of_inversions = 0;
    auto const size = a.size();

    if (0 == size)
        return number_of_inversions;

    set<T> set1;

    set1.insert(a[0]);

    for (auto i = 1; i < size; ++i)
    {
        set1.insert(a[i]);
        auto iter = set1.upper_bound(a[i]);
        number_of_inversions += std::distance(iter, set1.end());

    }

    return number_of_inversions;
}


int main()
{
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (auto& v: a)
  {
    std::cin >> v;
  }
//
  std::cout << get_number_of_inversions_by_set(a) << '\n';
  std::cout << get_number_of_inversions(a) << '\n';

}
