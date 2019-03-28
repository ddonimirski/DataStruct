#include <iostream>
#include <tuple>
#include <cmath>
#include <vector>
#include <iomanip>


using std::cout;
using std::cin;
using std::endl;

using point_t = std::tuple<int64_t, int64_t>;
using points_t = std::vector<point_t>;

auto get_x(point_t& p) { return std::get<0>(p); }
auto get_y(point_t& p) { return std::get<1>(p); }

auto& get_x(point_t const& p) { return std::get<0>(p); }
auto& get_y(point_t const& p) { return std::get<1>(p); }

auto distance(point_t const& p1, point_t const& p2)
{
    auto const xd = get_x(p1) - get_x(p2);
    auto const yd = get_y(p1) - get_y(p2);
    return sqrt((xd*xd) + (yd*yd));
}

auto closet_pair_of_points_naive(points_t const& points)
{
    if (points.size() <= 1)
    {
        return 0.0;
    }

    auto closet = distance(points[0], points[1]);

    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i+1; j < points.size(); ++j)
        {
            auto dist = distance(points[i], points[j]);
            if (dist < closet)
            {
                closet = dist;
            }
        }
    }

    return closet;
}


int main()
{
    size_t N;
    cin >> N;

    points_t points;
    points.reserve(N);

    for (size_t i = 0; i < N; ++i)
    {
        point_t p;
        cin >> get_x(p);
    }

    cout << std::setprecision(1) << closet_pair_of_points_naive(points) << endl;

}
