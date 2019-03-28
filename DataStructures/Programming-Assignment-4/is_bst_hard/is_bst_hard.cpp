#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::cerr;
using std::numeric_limits;

struct Node {
  long long int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};


#if defined PRINT
void print_tree(const vector<Node>& tree, int id_root)
{
    if (id_root < 0 || tree.empty())
        return;

    auto& root = tree[id_root];

    print_tree(tree, root.left);
    cerr << root.key << ' ';
    print_tree(tree, root.right);
}
#else
#define print_tree(v,a)
#endif


bool IsBst(const vector<Node>& tree, int id_root, long long int min_k , long long int max_k)
{
    if (id_root < 0 || tree.empty())
        return true;

    auto& root = tree[id_root];

    if (root.key < min_k || root.key >= max_k)
        return false;

    return IsBst(tree, root.left, min_k, root.key)
        && IsBst(tree, root.right, root.key, max_k);
}


bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  long long int constexpr IMIN = std::numeric_limits<int>::min();
  long long int constexpr IMAX = std::numeric_limits<int>::max();

  return IsBst(tree, 0, IMIN, IMAX+1);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }

  print_tree(tree, 0);

  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
