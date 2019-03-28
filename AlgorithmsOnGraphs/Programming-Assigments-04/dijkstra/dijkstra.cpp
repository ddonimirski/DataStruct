#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::numeric_limits;
using std::ostream;
using std::cout;
using std::endl;


struct vc
{
    int v;
    int c;

    friend bool operator < (vc const& l, vc const r)
    {
        return l.c < r.c;
    }

    friend ostream& operator << (ostream& os, vc const& v)
    {
        return os << v.v << ' ' << v.c;
    }
};

int distance(vector<vector<int> > &adj,
             vector<vector<int> > &cost,
             int s, int t)
{
  //write your code her
  vector<int> d(adj.size(), -1);

  priority_queue<vc> Q;
  d[s] = 0;
  Q.emplace(vc{s, d[s]});


  cout << s << ' ' << d[s] << endl;;

  while (!Q.empty())
  {
      auto u = Q.top();
      cout << u.v << endl;
      cout << u.c << endl;
      Q.pop();

      cout << u << ' ' << d[u.v] << ' ' << adj[u.v].size() << endl;

      for (auto v: adj[u.v])
      {
          if (d[v] > d[u.v] + cost[u.v][v])
          {
              d[v] = d[u.v] + cost[u.v][v];
              cout << "emplace " << vc{v, d[v]} << endl;
              Q.emplace(vc{v, d[v]});
          }
      }
  }

  return d[t];
}

int main()
{
  int n, m;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());

  for (int i = 0; i < m; i++)
  {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
