#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <iostream>


using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
using Adj = vector<vector<vector<int>>>;
using Len = long long;
using Queue =  vector< priority_queue< pair<Len, int>, vector<pair<Len,int>>, greater<pair<Len,int>> > >;

static auto const Len_INFINITY = std::numeric_limits<Len>::max();

class AStar
{
    // See the descriptions of these fields in the starter for friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<int> workset_;
    vector<bool> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;


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

    Len calculateShortestPath(int s, int t)
    {
        Len min_ = Len_INFINITY;
        for (auto i: workset_)
        {
            if (distance_[0][i] != Len_INFINITY && distance_[1][i] != Len_INFINITY)
            {
                int sum = distance_[0][i] + distance_[1][i];
                if (min_ > sum)
                {
                    min_ = sum;
                }
            }
        }

        return min_ == Len_INFINITY ? -1 : min_;
    }

    Len pi_func(int s, int t)
    {
        return sqrt(pow(xy_[s].first - xy_[t].first, 2) + pow(xy_[s].second - xy_[t].second, 2));
    }

public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n_, Len_INFINITY)), visited_(n), xy_(xy)
    { workset_.reserve(n); }

    // See the description of this method in the starter for friend_suggestion
    void clear()
    {
        for (int v = 0; v < visited_.size(); ++v)
        {
            distance_[0][v] = distance_[1][v] = Len_INFINITY;
            visited_[v] = false;
        }
        workset_.clear();
    }

    // See the description of this method in the starter for friend_suggestion
    void visit(Queue& q, int side, int v, Len dist)
    {
        // Implement this method yourself
        auto& qs = q[side];
        qs.push(make_pair(dist, v));
    }

    // Returns the distance from s to t in the graph
    Len query(int s, int t)
    {
        if (s == t)
        {
            return 0ll;
        }

        clear();
        Queue q(2);

        visit(q, 0, s, pi_func(s, t));
        distance_[0][s] = 0ll;
        visit(q, 1, t, pi_func(t, s));
        distance_[1][t] = 0ll;
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
            for (unsigned i = 0u; i < adj_[side][u].size(); ++i)
            {
                auto const v = adj_[side][u][i];

                int sum = distance_[side][u] + cost_[side][u][i];
                if (sum < distance_[side][v])
                {
                    distance_[side][v] = sum;
                    visit(q, side, v, sum  + pi_func(v, side?s:t));
                }
            }
            side = !side;
        }

        return calculateShortestPath(s, t);
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
