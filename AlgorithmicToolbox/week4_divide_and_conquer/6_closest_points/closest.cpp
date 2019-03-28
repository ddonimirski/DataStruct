#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using std::sort;
using std::vector;
using std::string;
using std::pair;
using std::min;
using std::cin;
using std::cout;
using std::endl;


using item_t = int64_t;
using res_t = long double;

struct Point
{
    item_t x, y;
};



res_t dist(Point const& p1, Point const& p2)
{
    return sqrt(static_cast<res_t>((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
}

res_t brute_force(Point points[], size_t n)
{
    auto min = std::numeric_limits<res_t>::max();

    for (size_t i = 0; i < n; ++i)
        for (auto j = i + 1; j < n; ++j)
        {
            auto const tmp_min = dist(points[i], points[j]);
            if (tmp_min < min)
                min = tmp_min;
        }

    return min;
}


res_t closest(Point X[], Point Y[], size_t n)
{
    if (n <= 3)
        return brute_force(X, n);

    auto mid = n/2;
    auto mid_point = X[mid];


    Point Yl[mid+1];
    Point Yr[n-mid-1];
    size_t li = 0, ri = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (Y[i].x <= mid_point.x)
            Yl[li++] = Y[i];
        else
            Yr[ri++] = Y[i];
    }

    auto const dl = closest(X, Yl, mid);
    auto const dr = closest(X + mid, Yr, n-mid);
    auto d = min(dl, dr);

    vector<Point> strip;
    strip.reserve(n);

    for (size_t i = 0; i < n; i++)
    {
        if (abs(Y[i].x - mid_point.x) < d)
        {
            strip.push_back(Y[i]);
        }
    }


    size_t const size = strip.size();
    for (size_t i = 0; i < size; ++i)
        for (size_t j = i+1; j < size && (strip[j].y - strip[i].y) < d; ++j)
            if (dist(strip[i],strip[j]) < d)
                d = dist(strip[i], strip[j]);

    return d;
}

res_t mimimal_distance(Point points[], size_t n)
{
    Point X[n];
    Point Y[n];
    for (size_t i = 0; i < n; i++)
    {
        Y[i] = X[i] = points[i];
    }

    sort(X, X+n, [](auto& p1, auto& p2)
            {
                return p1.x > p2.x;
            });

    sort(Y, Y+n, [](auto& p1, auto& p2)
            {
                return p1.y > p2.y;
            });

    return closest(X, Y, n);
}

int main()
{
    size_t n;
    std::cin >> n;
    auto* const points = new Point[n];

    for (size_t i = 0; i < n; i++) {
        auto& p = points[i];
        cin >> p.x >> p.y;
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(9) << mimimal_distance(points, n) << "\n";

    delete [] points;
}
