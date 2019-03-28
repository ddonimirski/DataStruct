#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using std::vector;
using std::cout;
using std::endl;

int lcs_rec(vector<int>& a, vector<int>& b, int sa, int sb)
{
    if (sa == 0 || sb == 0)
        return  0;

    if (a[sa-1] == b[sb-1])
        return  1 + lcs_rec(a,b, sa-1, sb-1);

    auto const tmp1 = lcs_rec(a,b, sa-1, sb);
    auto const tmp2 = lcs_rec(a,b, sa, sb-1);
    return  std::max(tmp1, tmp2);
}

template<class T>
class matrix
{
    T* const       _m; // raw memory
    size_t const   _w; // width
    size_t const   _h; // hight
    bool const    _alloc;

    T* get_row(int r) const { return _m + r * _w; }


    public:

    using value_t = T;

    matrix(T* m, size_t w, size_t h, bool z = true, bool alloc = false)
        : _m(alloc?new T[w*h]: m), _w(w), _h(h),_alloc(alloc)
    {
        if (z)
            memset(m, 0, w*h*sizeof(T));
    }

    ~matrix()
    {
        if (_alloc)
            delete [] _m;
    }


    T* operator [](int w) { return get_row(w); }

    T const* operator [](int w) const { return get_row(w); }

    T* begin() const { return get_row(0); };
    T* end() const { return get_row(_h); }
};


template<class M>
int lcs_mem(M& m, vector<int>& a, vector<int>& b, int sa, int sb)
{
    if (m[sa][sb] != 0)
        return m[sa][sb];

    typename M::value_t result;

    if (sa == 0 || sb == 0)
          result = 0;

    else if (a[sa-1] == b[sb-1])
        result =  1 + lcs_rec(a,b, sa-1, sb-1);

    else
    {
        auto const tmp1 = lcs_rec(a,b, sa-1, sb);
        auto const tmp2 = lcs_rec(a,b, sa, sb-1);
        result =  std::max(tmp1, tmp2);
    }

    m[sa][sb] = result;

    return 0;
}



int lcs_mem(vector<int>& a, vector<int>& b)
{
    auto const sa = a.size();
    auto const sb = b.size();
    int m[sa+1][sb+1];
    matrix<int> memo(reinterpret_cast<int*>(m), sa+1, sb+1);

    return lcs_mem(memo, a, b, sa-1, sb-1);
}

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  return lcs_rec(a,b,a.size(),b.size());
}


int lcs_bup(vector<int>& a, vector<int>& b)
{
    auto const sa = a.size();
    auto const sb = b.size();
    int m[sa+1][sb+1];

    for (auto ia = 0u; ia <= sa; ++ia)
    {
        for (auto ib = 0u; ib <= sb; ++ib)
        {
            if (ib == 0 || ia == 0)
                m[ia][ib] = 0;

            else if(a[ia-1] == b[ib-1])
            {
                m[ia][ib] = 1 + m[ia-1][ib-1];
            }

            else
            {
                m[ia][ib] = std::max(m[ia-1][ib], m[ia][ib-1]);
            }
        }
    }

    return m[sa][sb];
}


int main()
{
    std::ios::sync_with_stdio(false);

    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs_bup(a, b) << std::endl;
}
