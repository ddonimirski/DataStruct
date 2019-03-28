#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits>

using std::vector;
using std::string;
using std::max;
using std::min;
using std::endl;
using std::cout;

using item_t = int64_t;

template<class T>
class matrix
{
public:

    using index_t = size_t;
    using value_t = T;

    matrix(index_t r, index_t c, T* buf = nullptr, T&& v= T())
        : _rows(r), _cols(c), _buff(buf? buf : new T [r*c]), _new_buf(!buf)
    {
        //assert(r*c<limit)
        std::fill_n(_buff, r*c, v);
    }

    matrix(matrix&) = delete;

    ~matrix()
    {
        if (_new_buf)
            delete [] _buff;
    }

    T* buf() const
    {
        return _buff;
    }

[[nodiscard]]
    T const* operator[](size_t r) const
    {
        return get_row(r);
    }

    T* operator[](size_t r)
    {
        return get_row(r);
    }

[[nodiscard]]
    index_t rows() const
    {
        return _rows;
    }

[[nodiscard]]
    index_t cols() const
    {
        return _cols;
    }

    T* begin(index_t r = 0, index_t c = 0)
    {
        return get_row(r)+c;
    }

    T* end(index_t r, index_t c) const
    { return &get_cell(r,c);
    }

    T* end(index_t r) const
    {
        return end(r, _cols);
    }

    T* end() const
    {
        return end(_rows, _cols);
    }

    friend std::ostream& operator << (std::ostream& os, matrix<T> const&  m)
    {
        for (index_t r = 0; r < m.rows(); ++r)
        {
            for (index_t c = 0; c < m.cols(); ++c)
            {
                os << m[r][c] << ' ';
            }
            os << endl;
        }

        return os;
    }


private:
    index_t const _rows;
    index_t const _cols;
    T* _buff;
    bool _new_buf;

[[nodiscard]]
    T* get_row(index_t r) const
    {
        return buf()+_cols*r;
    }

[[nodiscard]]
    T& get_cell(index_t r, index_t c) const
    {
        return get_row(r)[c];
    }
};


auto eval(item_t a, item_t b, char op)
{
    if (op == '*')
    {
        a *= b;
    }
    else if (op == '+')
    {
        a += b;
    }
    else if (op == '-')
    {
        a -= b;
    }
    else
    {
        assert(0);
    }

    return a;
}



item_t get_maximum_value(const string &exp)
{
  //write your code here
  auto const n = (exp.size()+1)/2;
  matrix<item_t> m(n+1, n+1);
  matrix<item_t> M(n+1, n+1);
  //char  op[n+1]; // warning ISO
  vector<char> op(n+1);

  auto min_and_max = [&](int i, int j)
  {
      auto _min = std::numeric_limits<decltype(m[0][0])>::max();
      auto _max = std::numeric_limits<decltype(m[0][0])>::min();

      for (auto k = i; k < j; ++k)
      {
          auto val = eval(m[i][k], m[k+1][j], op[k]);

          if (_min > val) _min = val;
          if (_max < val) _max = val;

          val = eval(m[i][k], M[k+1][j], op[k]);

          if (_min > val) _min = val;
          if (_max < val) _max = val;

          val = eval(M[i][k], m[k+1][j], op[k]);

          if (_min > val) _min = val;
          if (_max < val) _max = val;

          val = eval(M[i][k], M[k+1][j], op[k]);

          if (_min > val) _min = val;
          if (_max < val) _max = val;
      }

      return std::make_tuple(_min, _max);
  };

  for (size_t i = 1; i <= n; i++)
  {
      int const val = exp[2*(i-1)]-'0';
      m[i][i] = M[i][i] = val;
      op[i] = exp[2*i-1];
  }

  for (size_t s = 1; s <= n-1; ++s)
  {
      for (size_t i = 1; i <= n-s; ++i)
      {
          auto const j = s + i;
          std::tie(m[i][j], M[i][j]) = min_and_max(i, j);
      }
  }

  return M[1][n];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
