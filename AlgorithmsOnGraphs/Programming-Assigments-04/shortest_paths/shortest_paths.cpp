#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::cerr;
using std::endl;

auto const IMAX = std::numeric_limits<long long>::max();

#if defined DEBUG

template<class T>
using graph = vector<vector<T>>;

template<class T>
void prc(T const& c)
{
    for (auto const v: c)
        cerr << v << ' ';
    cerr << endl;
}


template<class TA, class TC>
void prg(graph<TA>& g, graph<TC>& c)
{
    for (auto u = 0u; u < g.size(); ++u)
        for (auto id = 0u; id < g[u].size(); ++id)
        {
            auto const v = g[u][id];
            cerr << u << "->" << v << '(' << c[u][id] <<')' << ' ';
        }

    cerr << endl;
}

#else
#define prc(...)
#define prg(...)
#endif


struct vc
{
    long long v;
    long long c;

    friend bool operator < (vc const& l, vc const& r)
    {
        return l.c < r.c;
    }
};


void shortest_paths(vector<vector<long long> > &adj,
        vector<vector<long long> > &cost,
        int s,
        vector<long long> &distance,
        vector<int> &reachable,
        vector<int> &shortest)
{
    //write your code here
    prg(adj, cost);

    auto relax = [&distance, &reachable, &adj, &cost](int u)
    {
        bool ret = true;

        auto const dist_u = distance[u];
        if (dist_u != IMAX)
        {
            auto const& edges = adj[u];
            auto const& ecost = cost[u];

            for (auto id = 0u; id < edges.size(); ++id)
            {
                auto const v = edges[id];
                auto const dw  = dist_u + ecost[id];
                if (distance[v] > dw)
                {
                    distance[v] = dw;
                    reachable[v] = 1;
                    ret = false;
                }
            }
        }
        return ret;
    };

    distance[s] = 0;
    reachable[s] = 1;

    auto V = adj.size();

    bool cont = true;
    while(--V && cont)
    {
        cont = true;
        for (auto u = 0u; u < adj.size(); ++u)
        {
            cont = relax(u);
        }
    }


    priority_queue<vc> vertex;
    auto mark_cycle = [&distance, &shortest, &adj, &cost, &vertex](int u)
    {
        auto const dist_u = distance[u];
        if (dist_u != IMAX)
        {
            auto const& edges = adj[u];
            auto const& ecost = cost[u];

            for (auto id = 0u; id < edges.size(); ++id)
            {
                auto const v = edges[id];
                auto const dw  = dist_u + ecost[id];
                if (distance[v] > dw)
                {
                    distance[v] = dw;
                    if (shortest[v])
                    {
                        vertex.push({v, ecost[id]});
                        shortest[v] = 0;
                    }
                }
            }
        }
    };


    for (auto u = 0u; u < adj.size(); ++u)
    {
        mark_cycle(u);
    }

    vector<bool> vis(adj.size(), false);

    while (!vertex.empty())
    {
        auto const u = vertex.top().v;
        vertex.pop();

        if (!vis[u])
        {
            vis[u] = true;
            shortest[u] = 0;

            //auto const dist_u = distance[u];
            auto const& edges = adj[u];
            auto const& ecost = cost[u];

            for (auto id = 0u; id < edges.size(); ++id)
            {
                auto const v = edges[id];
                //auto const dw  = dist_u + cost[u][id];
                //if (distance[v] > dw)
                {
                    if (!vis[v] && shortest[v])
                    {
                        vertex.push(vc{v, ecost[id]});
                    }
                }
            }
        }
    }

    distance[s] = 0;
    shortest[s] = 1;
}

int main()
{
    int n, m, s;
    std::cin >> n >> m;

    vector<vector<long long>> adj(n, vector<long long>());
    vector<vector<long long>> cost(n, vector<long long>());

    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }

    std::cin >> s;
    s--;

    vector<long long> distance(n, IMAX);
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);

    shortest_paths(adj, cost, s, distance, reachable, shortest);

    for (int i = 0; i < n; i++)
    {
        if (!reachable[i])
        {
            std::cout << "*\n";
        }
        else if (!shortest[i])
        {
            std::cout << "-\n";
        }
        else
        {
            std::cout << distance[i] << "\n";
        }
    }
}
