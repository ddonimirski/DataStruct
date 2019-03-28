#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>

using std::cout, std::cin, std::endl;
using std::vector;


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


int optimal_weight(int W, const vector<int> &ws) {

    matrix<int> weights(W+1,ws.size()+1);

    for (decltype(ws.size()) i = 1; i <= ws.size(); ++i)
    {
        auto const item_w = ws[i-1];
        for (int w = 1; w <= W; ++w)
        {
            weights[w][i] = weights[w][i-1];
            if (item_w <= w)
            {
                auto const tmp_w = weights[w-item_w][i-1] + item_w;
                if (tmp_w > weights[w][i])
                {
                    weights[w][i] = tmp_w;
                }
            }
        }
    }

    return weights[W][ws.size()];
}

using val_t = std::tuple<int,bool>;

int _optimal_weight_rec(int W, const vector<int> &ws, vector<val_t>& vals)
{
    auto& [val,set] = vals[W];
    if (set)
        return val;

    //vals[W] = std::make_tuple(0, false);
    for (size_t i = 1; i <= ws.size(); ++i)
    {
        auto const iw = ws[i-1];
        if (iw < W)
        {
            auto const v = _optimal_weight_rec(W-iw, ws, vals) + iw;
            if (v > val)
            {
                vals[W] = std::make_tuple(v, true);
            }
        }
    }

    auto[ret, rset] = vals[W];
    return ret;
}

int optimal_weight_rec(int W, const vector<int> &ws)
{
    vector<val_t> vals(W+1);
    return _optimal_weight_rec(W, ws, vals);
}


int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
  std::cout << optimal_weight_rec(W, w) << '\n';
}
