#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using std::reverse;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x)
{
    //write your code here

    if (!used[x])
    {
        used[x] = true;

        for (auto v : adj[x])
        {
            if (!used[v])
            {
                dfs(adj, used, order, v);
            }
        }

        order.push_back(x);
    }
}

vector<int> toposort(vector<vector<int> > adj)
{
    vector<int> used(adj.size(), 0);
    vector<int> order;
    //write your code here
    vector<int> sources;

    for (auto rec: adj)
    {
        for (auto v: rec)
        {
            used[v] = 1;
        }
    }

    for (auto i = 0u; i < used.size(); ++i)
    {
        if (!used[i])
        {
            sources.push_back(i);
        }
        used[i] = 0;
    }

    for (auto s: sources)
        dfs(adj, used, order, s);

    reverse(order.begin(), order.end());

    return order;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    vector<int> order = toposort(adj);
    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
