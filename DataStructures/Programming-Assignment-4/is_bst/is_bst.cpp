#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::endl;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBst(const vector<Node>& tree, int id_root, int& id_prev)
{
    if (id_root < 0 || id_root >= tree.size())
        return true;
    auto& root = tree[id_root];

    if (!IsBst(tree, root.left, id_prev))
        return false;

    if (id_prev >= 0 && id_prev < tree.size() && root.key <= tree[id_prev].key)
        return false;

    id_prev = id_root;

    return IsBst(tree, root.right, id_prev);

}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  int prev = -1;

  return IsBst(tree, 0, prev);
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
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
