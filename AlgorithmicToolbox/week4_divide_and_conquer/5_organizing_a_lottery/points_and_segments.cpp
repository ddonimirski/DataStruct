#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

using point_t = int;

struct segment_t {
    point_t start, end;
};

using segments_t  = vector<senment_t>;
using points_t = vector<point_t>;

int check_hit(segments_t const& seg, point_t point)
{
}

points_t fast_count_segments(segments_t& segments, points_t const& points)
{
    vector<int> cnt(points.size());
    //write your code here
    sort(segments.begin(), segments.end(), [](segment_t const& s1, segment_t const& s2)
            {
                if (s1.start < s2.start) return true;
                if (s1.start > s2.start) return false;
                return s1.end < s2.end;
            });



    return std::move(cnt);
}

vector<int> naive_count_segments(segments_t& segments, points_t const& points)
{
  vector<int> cnt(points.size());

  for (size_t i = 0; i < points.size(); i++)
  {
    for (size_t j = 0; j < segments.size(); j++)
    {
      cnt[i] += segments[j].start <= points[i] && points[i] <= segments.end[j];
    }
  }
  return std::move(cnt);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  segments_t seg;
  for (size_t i = 0; i < starts.size(); i++)
  {
    std::cin >> seg[i].start >> seg[i].end;
  }

  points_t points(m);
  for (size_t i = 0; i < points.size(); i++)
  {
    std::cin >> points[i];
  }

  //use fast_count_segments
  vector<int> cnt = naive_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++)
  {
    std::cout << cnt[i] << ' ';
  }
}
