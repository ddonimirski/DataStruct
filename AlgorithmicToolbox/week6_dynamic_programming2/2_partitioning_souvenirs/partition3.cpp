#include <iostream>
#include <vector>
#include <cstring>
#include <numeric>

using std::vector;

bool partition3(vector<int> &A) {
  //write your code here
  auto const n = A.size();

  auto sum = std::accumulate(A.begin(), A.end(), 0ul);

  if (sum%3) return false;


  return false;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
