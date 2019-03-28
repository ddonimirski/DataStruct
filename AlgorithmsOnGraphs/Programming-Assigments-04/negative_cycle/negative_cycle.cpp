#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


using std::vector;
using std::numeric_limits;
using std::cerr;
using std::endl;
using std::fill;

template<class T>
using graph = vector<vector<T>>;

vector<int> dist;
vector<int> pred;

#if defined DEBUG
template<class T>
void prc(T const& c)
{
	for (auto const v: c)
		cerr << v << ' ';
	cerr << endl;
}

template<class T>
void prg(graph<T> const& g, graph<int> const& c)
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

#define CORMEN

#if !defined CORMEN
auto last_relaxed = -1;
#endif

bool relax_all_edges(vector<int> edges, vector<int> costs, int u)
{
	bool ret = false;

	auto const dist_u = dist[u];
	if (dist_u != numeric_limits<int>::max())
		for (auto id = 0u; id < edges.size(); ++id)
		{
			auto const v = edges[id];
			if (dist[v] > dist_u + costs[id])
			{
				dist[v] = dist_u + costs[id];
				pred[v] = u;
				ret = true;
#if !defined CORMEN
				last_relaxed = v;
#endif
			}
		}
	prc(dist);

	return ret;
}


int negative_cycle(graph<int> &adj, graph<int> &cost)
{
	//write your code here
	prg(adj, cost);

	dist = std::move(vector<int>(adj.size(), numeric_limits<int>::max()));
	pred = std::move(vector<int>(adj.size(), -1));

	for (auto s = 0u; s < adj.size(); ++s)
	{
		dist[s] = 0;

		auto V = adj.size();
		while(--V)
		{
			bool ff = true;
			for (auto u = 0u; u < adj.size(); ++u)
			{

				if (relax_all_edges(adj[u], cost[u], u))
				{
					ff = false;
				}
			}

			if (ff)
				break;
		}


#if defined CORMEN
		for (auto u = 0u; u < adj.size(); ++u)
		{
			if (relax_all_edges(adj[u], cost[u], u))
				return 1;
		}
#else
		auto v = last_relaxed;
		V = adj.size();
		while (--V)
		{
			v = pred[v];
			if (v == last_relaxed)
				return 1;
		}
#endif
		fill(begin(dist), end(dist), numeric_limits<int>::max());
		fill(begin(pred), end(pred), -1);
	}

	return 0;
}



int main()
{
    int n, m;
    std::cin >> n >> m;
    graph<int> adj(n, vector<int>());
    graph<int> cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
