#include <iostream>
#include <vector>
#include <functional>

using std::vector;
using std::pair;
using std::cerr;
using std::endl;
using std::function;

int acyclic(vector<vector<int> > &adj)
{
    //write your code here
    vector<bool> vis(adj.size());
    vector<bool> rec(adj.size());

    function<bool(int)> exp = [&adj, &vis, &rec, &exp](int x)
    {
        if (!vis[x])
        {
            vis[x] = true;
            rec[x] = true;

            for (auto v: adj[x])
            {
                if (!vis[v] && exp(v))
                {
                    return true;
                }
                else if(rec[v])
                {
                    return true;
                }
            }
        }

        rec[x] = false;
        return false;
    };

    //must be check for all vertex
    for (auto i = 0u; i < adj.size(); ++i)
    {
        if (exp(i))
            return true;
    }

    return false;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());

    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }

    std::cout << acyclic(adj);
}
