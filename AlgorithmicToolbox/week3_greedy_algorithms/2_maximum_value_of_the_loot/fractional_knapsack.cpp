#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using std::vector;
using std::sort;

double get_optimal_value_first(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  vector<int> ids(weights.size());

  for (int i = 0; i < ids.size(); ++i)
  {
      ids[i] = i;
  }

  sort(ids.begin(), ids.end(), [&](int i1, int i2)
          {
            return values[i1]/weights[i1] > values[i2]/weights[i2];
          });

  for (auto const i: ids)
  {
      if (capacity >= weights[i])
      {
          capacity -= weights[i];
          value += values[i];
      }
      else
      {
          value += capacity * (static_cast<double>(values[i])/weights[i]);
          break;
      }

  }

  return value;
}



int get_max_index(vector<int>& weights, vector<int>& values)
{
    int max_i = 0;
    double max = static_cast<double> (values[max_i]) / weights[max_i];

    for (int i = 1; i < weights.size(); i++)
    {
        if (!weights[i])
            continue;

        auto const tmp = static_cast<double>(values[i])/weights[i];
        if (tmp > max)
        {
            max = tmp;
            max_i = i;
        }
    }
    return max_i;
}

double get_optimal_value(int capacity, vector<int>& weights, vector<int>& values)
{

    double value = 0.0;

    for (int i = 0; i < weights.size() && capacity != 0; i++)
    {
        auto const index = get_max_index(weights, values);
        auto const w = std::min(capacity, weights[index]);
        value += w * static_cast<double> (values[index]) / weights[index];
        weights[index] -= w;
        capacity -= w;
    }

    return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
