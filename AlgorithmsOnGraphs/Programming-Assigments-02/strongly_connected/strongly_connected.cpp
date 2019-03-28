#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>

using std::vector;
using std::pair;
using std::stack;
using std::begin;
using std::endl;
using std::cout;
using std::endl;
using std::ostream;
using std::fill;
using std::move;


template<class T>
using graph = vector<vector<T>>;

enum {
    WHITE = 0,
    GRAY,
    BLACK
};

template<class INT = int>
struct result
{
    vector<INT> col;
    stack<INT> st;

    void (*post_action)(result& res, INT u);

    static void nop(result&, INT){}
    static void push(result& res, INT u) { res.st.push(u); }

    result(size_t size): col(size), post_action(nop)
    {
        fill(begin(col),end(col),WHITE);
    }

    friend ostream& operator << (ostream& o, result const& res)
    {
        prc_with_id(res.col, 0, res.col.size(), o);
        return o;
    }


};

void DFS_vis(graph<int> const& g, int u, result<int>& r)
{
    auto& col = r.col;
    col[u] = GRAY;

    for (auto const v: g[u])
    {
        if (col[v] == WHITE)
        {
            DFS_vis(g, v, r);
        }
    }

    col[u] = BLACK;
    r.post_action(r, u);
}

template<class T>
void DFS(graph<T>& g, result<T>& r) // post_action for result shoud be set to push
{
    r.post_action = &result<int>::push;
    for (auto v = 0u; v < g.size(); ++v)
        if (r.col[v] == WHITE)
            DFS_vis(g, v, r);
}

int DFS_exp(graph<int>& g, result<int>& r) // post_action for result should be set to nop
{
    int res = 0;
    auto& st = r.st;
    r.post_action = &result<int>::nop;
    auto& col = r.col;

    fill(begin(col), end(col), WHITE);

    while (!st.empty())
    {
        auto u = st.top();
        st.pop();
        if (col[u] == WHITE)
        {
            DFS_vis(g, u, r);
            ++res;
        }
    }

    return res;
}

graph<int> createReverse(graph<int>& adj)
{
    graph<int> gR(adj.size());

    for (auto vs = 0u; vs<adj.size(); ++vs)
    {
        for (auto r = 0u; r < adj[vs].size(); ++r)
        {
            gR[adj[vs][r]].push_back(vs);
        }
    }

    return move(gR);
}

int number_of_strongly_connected_components(vector<vector<int> >& adj)
{
    //write your code here
    result<int> res(adj.size());
    DFS(adj, res);
    auto GR = createReverse(adj);
    return DFS_exp(GR, res);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << number_of_strongly_connected_components(adj);
}
