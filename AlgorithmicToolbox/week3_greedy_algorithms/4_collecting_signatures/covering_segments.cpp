#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;
using std::sort;

struct Segment {
  int start, end;
};

static int n;

vector<int> optimal_points(vector<Segment> &segments)
{
    sort(begin(segments), end(segments), [](Segment const& s1, Segment const& s2) { return s1.end < s2.end; });

    vector<int> points;
    auto point = segments[0].end;
    points.push_back(point);

    for (size_t i = 0; i < segments.size(); ++i)
    {
        if (point < segments[i].start || point > segments[i].end)
        {
            point = segments[i].end;
            points.push_back(point);
        }
    }
    return points;
}

int main()
{
  std::cin >> n;
  vector<Segment> segments(n);

  for (size_t i = 0; i < segments.size(); ++i)
  {
    std::cin >> segments[i].start >> segments[i].end;
  }

  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";

  for (size_t i = 0; i < points.size(); ++i)
  {
    std::cout << points[i] << " ";
  }
}
