#include <iostream>
#include <vector>
#include <functional>

using std::vector;
using std::pair;
using std::function;

int number_of_components(vector<vector<int> > &adj)
{
    int res = 0;

    //write your code here
    vector<bool> vis(adj.size());

#if defined SUPPORT_FOR_AUTO_AS_PARAMITER

    auto exp = [&adj, &vis](int x)
    {
        auto exp_imp = [&adj, &vis](int x, auto& exp_ref) -> void
        {
            for (auto v: adj[x])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    exp_ref(v, exp_ref);
                }
            }
        };

        exp_imp(x, exp_imp);
    };

#else

    function<void(int)> exp = [&adj, &vis, &exp](int x)
    {
        for (auto v: adj[x])
        {
            if (!vis[v])
            {
                vis[v] = true;
                exp(v);
            }
        }
    };

#endif


    for (int i = 0; i < vis.size(); ++i)
    {
        if (vis[i])
            continue;
        ++res;

        exp(i);
    }

    return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
