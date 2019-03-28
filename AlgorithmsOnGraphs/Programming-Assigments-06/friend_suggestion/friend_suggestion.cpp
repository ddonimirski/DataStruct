#include <iostream>
//#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector< priority_queue< pair<Len, int>, vector<pair<Len,int> > ,greater<pair<Len,int>> > > Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra
{
    // Number of nodes
    int n_;

    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;

    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;

    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;

    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<bool> visited_;


    int extractMin(Queue& q, int side)
    {
        if (!q[side].empty())
        {
            auto const v = q[side].top();
            q[side].pop();
            return v.second;
        }

        return -1;
    }


    Len calculateShortestPath()
    {
        Len min = INFINITY;
        for (auto i: workset_)
        {
            if (distance_[0][i] != INFINITY && distance_[1][i] != INFINITY)
            {
                int sum = distance_[0][i] + distance_[1][i];
                if (min > sum)
                {
                    min = sum;
                }
            }
        }

        return min == INFINITY ? -1 : min;
    }

public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(n)
    { workset_.reserve(n); }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear()
    {
        for (int v = 0; v < visited_.size(); ++v)
        {
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[v] = false;
        }
        workset_.clear();
    }

    // Processes visit of either forward or backward search 
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue& q, int side, int v, Len dist)
    {
        // Implement this method yourself
        distance_[side][v] = dist;
        auto& qs = q[side];
        qs.push(make_pair(dist, v));
    }

    // Returns the distance from s to t in the graph.
    Len query(int s, int t)
    {
        if (s == t)
            return 0;

        clear();
        Queue q(2);

        visit(q, 0, s, 0);
        visit(q, 1, t, 0);

        // Implement the rest of the algorithm yourself
        int side = 0;

        while(true)
        {
            auto const u = extractMin(q, side);

            if (u == -1 || visited_[u])
            {
                break;
            }

            visited_[u] =  true;
            workset_.push_back(u);
            for (uint32_t i = 0u; i < adj_[side][u].size(); ++i)
            {
                auto const v = adj_[side][u][i];
                int sum = distance_[side][u] + cost_[side][u][i];
                if (sum < distance_[side][v])
                {
                    visit(q, side, v, sum);
                }
            }
            side = !side;
        }

        return calculateShortestPath();
    }
};

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
    std::ios::sync_with_stdio(false);

    int n, m;
    //scanf("%d%d", &n, &m);
    cin >> n >> m;
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));

    for (int i=0; i<m; ++i)
    {
        int u, v, c;
        //scanf("%d%d%d", &u, &v, &c);
        cin >> u >> v >> c;
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    Bidijkstra bidij(n, adj, cost);

    int t;
    //scanf("%d", &t);
    cin >> t;
    for (int i=0; i<t; ++i)
    {
        int u, v;
        //scanf("%d%d", &u, &v);
        cin >> u >> v;
        //printf("%lld\n", bidij.query(u-1, v-1));
        cout << bidij.query(u-1, v-1) << endl;
    }
}
