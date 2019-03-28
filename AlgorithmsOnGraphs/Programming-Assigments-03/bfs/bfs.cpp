#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

enum visit_status: unsigned char
{
    WHITE = 0u,
    GREY,
    BLACK
};



int distance(vector<vector<int> > &adj, int s, int t)
{
    //write your code here
    vector<visit_status> vis(adj.size(), WHITE);
    vector<unsigned> dist(adj.size(), -1);
    queue<int> q;

    dist[s] = 0;
    vis[s] = GREY;
    q.push(s);

    while(!q.empty())
    {
        auto u = q.front();
        q.pop();
        auto const next_dist = dist[u] + 1;

        for (auto v: adj[u])
        {
            if (vis[v] == WHITE)
            {
                if (v == t)
                    return next_dist;

                dist[v] = next_dist;
                vis[v] = GREY;
                q.push(v);
            }
        }
        vis[u] = BLACK;
    }

    return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
