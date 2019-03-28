#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>


using std::vector;
using std::priority_queue;

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

double minimum_distance(vector<int> x, vector<int> y)
{
    double result = 0.;

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

    while(!pior.empty())
    {
        auto vv = pior.top();
        pior.pop();
        if (!uu.connected(vv.v1, vv.v2))
        {
            result += vv.c;
            uu.join(vv.v1, vv.v2);
        }
    }

    return result;
}

int main()
{
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
