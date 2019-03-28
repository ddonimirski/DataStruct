#include <iostream>

int get_change(int m) {

    int c = m/10;
    if (int r = m%10)
    {
        c += r/5 + r%5;
    }
    return c;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
