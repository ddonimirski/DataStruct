#include <iostream>
#include <string>
#include <functional>

using std::string;

auto constexpr PENALTY = 1;
#if defined LEV
auto constexpr QPENALTY = 2;
#else
auto constexpr QPENALTY = 1;
#endif


#if defined PRINT_ALIGMENT
template<class U>
struct matrix {

    U const* _d;
    int const _i;
    int const _j;

    U const* operator[](int i) const
    {
        return static_cast<U const*>(_d + i * _i);
    }

    matrix(U *d, int i, int j): _d(d), _i(i), _j(j)
    {}

};

template<class T>
void print_aligment(std::string const& str1, std::string const& str2, std::string& top, string& bottom, T const& dist, int i, int j)
{

    if (0 == i && 0 == j)
    {
        return;
    }

    if (i > 0 && dist[i][j] == dist[i-1][j]+1)
    {
        print_aligment(str1, str2, top, bottom, dist, i-1, j);
        top.push_back(str1[i-1]);
        bottom.push_back('-');
    }

    else if (j > 0 && dist[i][j] == dist[i][j-1]+1)
    {
        print_aligment(str1, str2, top, bottom, dist, i, j-1);
        top.push_back('-');
        bottom.push_back(str2[j-1]);
    }

    else
    {
        print_aligment(str1, str2, top, bottom, dist, i-1, j-1);
        top.push_back(str1[i-1]);
        bottom.push_back(str2[j-1]);
    }
}

template<class T>
void print_aligment(std::string const& str1, std::string const& str2, T const * d)
{
    std::string top;
    std::string bottom;

    matrix const dist(d, str1.size()+1, str2.size()+1);

    print_aligment(str1, str2, top, bottom, dist, str1.size(), str2.size());

    std::cout << top << std::endl;
    std::cout << bottom << std::endl;
}

#else
#define print_aligment(s1, s2, d) do {} while(0)// not used
#endif

int edit_distance(const string &str1, const string &str2) {

    auto const str1_size = str1.size() + 1u;
    auto const str2_size = str2.size() + 1u;

    int dist[str1_size][str2_size];

    for (auto i1 = 0u; i1 < str1_size; ++i1) //
    {
        dist[i1][0u] = i1;
    }

    for (auto i2 = 0u; i2 < str2_size; ++i2) // 
    {
        dist[0u][i2] = i2;
    }

    for (auto i1 = 1u; i1 < str1_size; ++i1)
    {
        for (auto i2 = 1u; i2 < str2_size; ++i2)
        {
            dist[i1][i2] = dist[i1-1u][i2] + PENALTY; // top
            auto const bottom = dist[i1][i2-1u] + PENALTY; 
            if (dist[i1][i2] > bottom)
            {
                dist[i1][i2] = bottom;
            }
            auto const cross  = dist[i1-1u][i2-1u]+(str1[i1-1u] == str2[i2-1u]?  0: QPENALTY);
            if (dist[i1][i2] > cross)
            {
                dist[i1][i2] = cross;
            }
        }
    }


    print_aligment(str1, str2, reinterpret_cast<int const*>(&dist));

    return dist[str1.size()][str2.size()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
