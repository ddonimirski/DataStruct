#include <iostream>
#include <vector>
#include <functional>
#include <stack>

using std::vector;
using std::pair;
using std::function;
using std::stack;
using std::cerr;
using std::endl;


int reach(vector<vector<int> > &adj, int x, int y)
{
    //write your code here
    vector<bool> vis(adj.size());

#if defined SUPPORT_FOR_AUTO_AS_PARAMITER
    auto exp = [&adj, &vis, y](int x)
    {
        auto exp_imp = [&adj, &vis, y](int x, auto& exp_ref)
        {
            for (auto v: adj[x])
            {
                if (y == v)
                    return true;

                if (!vis[v])
                {
                    vis[v] = true;
                    exp_ref(v, exp_ref);
                }
            }

            return false;
        };

        return exp_imp(x, exp_imp);
    };
#elif defined FUNCTION_SOLUTION

    function<bool(int)> exp = [&adj, &vis, &exp, y](int x)
    {
        for (auto v: adj[x])
        {
            if (y == v)
            {
                return true;
            }

            if (!vis[v])
            {
                vis[v] = true;
                if (exp(v))
                {
                    return true;
                }
            }
        }

        return false;
    };
#else // iteration

    auto exp = [&adj, &vis, y](int x)
    {
        stack<int> st;
        st.push(x);

        while (!st.empty())
        {
            auto v = st.top();
            st.pop();

            if (y == v)
                return true;

            if (!vis[v])
            {
                vis[v] = true;
                for (auto c: adj[v])
                {
                    if (!vis[c])
                    {
                        st.push(c);
                    }
                }
            }
        }

        return false;
    };

#endif

    return exp(x);
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
        adj[y - 1].push_back(x - 1);
    }

    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
