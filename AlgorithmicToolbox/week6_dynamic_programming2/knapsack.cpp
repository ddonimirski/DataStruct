#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using item_t = std::tuple<int,int>;
using items_t = std::vector<item_t>;
using std::cout, std::cin, std::endl;
using std::vector;

[[nodiscard]]
inline item_t make_item(int w, int v)
{
    return std::make_tuple(w, v);
}


[[nodiscard]]
int knapsack_with_repetitions(int weight, items_t const& items)
{
    vector<int> values(weight+1);

    for (int w = 1; w <= weight; ++w)
    {
        //values[w] = 0; // all values are set to 0// set minimum value for knapsack weight == w 
        for (size_t i = 0; i < items.size(); ++i)
        {
            auto const [item_weight, item_value] = items[i];
            if (item_weight <= w)
            {
                auto const tmp_value = values[w - item_weight] + item_value;
                if (tmp_value > values[w])
                {
                    values[w] = tmp_value;
                }
            }
        }
    }

    return values[weight];
}


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

[[nodiscard]]
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
    {
        return &get_cell(r,c);
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


[[nodiscard]]
int knapsack_without_repetitions(int weight, items_t const& items)
{
    auto const n = items.size();
    auto const buf_size = (weight+1)*(n+1);

    int buf[buf_size];
    std::fill(buf, buf+buf_size, 0);
    matrix values(weight+1, n+1, buf);


    for (decltype(items.size()) i = 1; i<= n; ++i)
    {
        auto const [item_weight, item_value] = items[i-1];
        for (decltype(weight) w = 1; w <= weight; ++w)
        {
            values[w][i] = values[w][i-1];
            if (item_weight <= w)
            {
                auto const val = values[w-item_weight][i-1] + item_value;
                if (val > values[w][i])
                    values[w][i] =  val;
            }
        }
    }

    return values[weight][n];
}

int main()
{
    int weight;
    cin >> weight;

    int n;
    cin >> n;

    items_t items;
    items.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        int w, v;
        cin >> w >> v;
        items.push_back(make_item(w,v));
    }

    cout << knapsack_with_repetitions(weight, items) << endl;
    cout << knapsack_without_repetitions(weight, items) << endl;
}
