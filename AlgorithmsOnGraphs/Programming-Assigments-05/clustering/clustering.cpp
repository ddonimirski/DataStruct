#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>
#include <set>

using std::vector;
using std::pair;
using std::priority_queue;
using std::cout;
using std::endl;


struct vc
{
    unsigned v1, v2;
    double c;

    friend bool operator < (vc const& l, vc const& r)
    {
        return l.c > r.c;
    }
};


struct disjoin_set
{
    vector<int> _buf;
    vector<int> _sz;

    disjoin_set(size_t s)
    {
        for (auto i = 0u; i < s; ++i)
        {
            _buf.push_back(i);
            _sz.push_back(1);
        }
    }

    int base(int i)
    {
        while (i != _buf[i])
        {
            _buf[i] = _buf[_buf[i]];
            i = _buf[i];
        }

        return i;
    }

    bool connected(int i, int j)
    {
        return base(i) == base(j);
    }

    void join(int i, int j)
    {
        auto const ri = base(i);
        auto const rj = base(j);

        if (_sz[i] < _sz[j])
        {
            _buf[ri] = rj;
            _sz[rj] += _sz[ri];
        }

        else
        {
            _buf[rj] = ri;
            _sz[ri] += _sz[rj];
        }
    }
};


double clustering(vector<int> x, vector<int> y, int k)
{
    //write your code here
    auto dist_cost = [&x, &y](unsigned i, unsigned j)
    {
        auto const dx = x[i] - x[j];
        auto const dy = y[i] - y[j];
        auto const x2 = dx * dx;
        auto const y2 = dy * dy;
        return std::sqrt(static_cast<double>(x2 + y2));
    };

    priority_queue<vc> pior;

    //write your code here
    for (auto i = 0u; i < x.size()-1; ++i)
    {
        for (auto j = i + 1; j < y.size(); ++j)
        {
            auto const c = dist_cost(i , j);
            pior.emplace(vc { i, j, c});
        }
    }

    disjoin_set uu(x.size());

    auto K = x.size();
    while(!pior.empty())
    {
        auto const vv = pior.top();
        pior.pop();
        if (!uu.connected(vv.v1, vv.v2))
        {
            uu.join(vv.v1, vv.v2);
            if (K-- == k)
            {
                return vv.c;
            }
        }
    }

    return -1;
}

int main()
{
    size_t n;
    int k;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
