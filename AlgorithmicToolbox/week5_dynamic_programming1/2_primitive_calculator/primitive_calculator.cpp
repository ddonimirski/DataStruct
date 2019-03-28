#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

#define MEM

#if defined ORIGINAL
vector<int> optimal_sequence(int n)
{
  std::vector<int> sequence;
  while (n >= 1)
  {
    sequence.push_back(n);
    if (n % 3 == 0) { n /= 3; }
    else if (n % 2 == 0)
    {
      n /= 2;
    }
    else
    {
      --n;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}
#elif defined RECUR

vector<int> optimal_sequence(int n)
{
    vector<int> seq;

    if (n>=1)
    {
        seq = optimal_sequence(n-1);

        if (n % 3 == 0)
        {
            auto vec1 = optimal_sequence(n/3);

            if (seq.size() > vec1.size())
            {
                seq = std::move(vec1);
            }
        }

        if (n % 2 == 0)
        {
            auto vec1 = optimal_sequence(n/2);

            if (seq.size() > vec1.size())
            {
                seq = std::move(vec1);
            }
        }

        seq.push_back(n);
    }

    return std::move(seq);
}

#elif defined MEM

vector<int> optimal_sequence(int number)
{
    std::vector<int32_t> min_steps(number + 1);
    std::vector<int32_t> predecessor(number + 1);

    for (int32_t i = 2; i <= number; i++)
    {
        min_steps[i] = min_steps[i-1] + 1;
        predecessor[i] = i - 1;

        if (i % 3 == 0)
        {
            if (min_steps[i/3] < min_steps[i])
            {
                min_steps[i] = min_steps[i/3] + 1;
                predecessor[i] = i/3;
            }
        }

        if (i % 2 == 0)
        {
            if (min_steps[i/2] < min_steps[i])
            {
                min_steps[i] = min_steps[i/2] + 1;
                predecessor[i] = i/2;
            }
        }
    }

    vector<int> s;
    s.reserve(predecessor.size());
    for (int32_t i = number; i != 0; i = predecessor[i]) {
        s.push_back(i);
    }

    reverse(s.begin(), s.end());

    return std::move(s);
}

#endif

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);

  std::cout << sequence.size() - 1 << std::endl;

  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }

}
