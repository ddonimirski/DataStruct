#include <iostream>
#include <vector>

using std::vector;

vector<int> summands;

void optimal_summands(int n) {
  //write your code here
    for (int i = 1; i <= n; ++i)
    {
        n -= i;
        if (n <= i)
            summands.push_back(n+i);
        else
        {
            summands.push_back(i);
            if (n==0)
                break;
        }
    }
}

int main()
{
    int n;
    std::cin >> n;
    optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
