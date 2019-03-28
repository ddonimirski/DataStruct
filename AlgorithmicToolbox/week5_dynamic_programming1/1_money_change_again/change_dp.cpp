#include <iostream>
#include <cstring>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

// m 1 3 4
static int const coins[] = {1 ,3, 4};
static int const n_coins = sizeof(coins)/sizeof(int);
static int const min_money = 1;
static int const max_number = std::numeric_limits<int>::max();

static int* min_coins;

int get_change_rec(int m)
{
    if (0 == m)
        return 0;

    int min_num_coins = max_number;

    for (int ic = 0; ic < n_coins; ++ic)
    {
        auto const coin =  coins[ic];
        if (m >= coin)
        {
            auto const num_coins = get_change_rec(m - coin) + 1;
            if (min_num_coins > num_coins)
            {
                min_num_coins = num_coins;
            }
        }
    }

    return min_num_coins;
}

int get_change_dp(int m)
{
    if (0 == m)
        return 0;

    if (min_coins[m] == 0)
    {
        int min_num_coins = max_number;

        for (int ic = 0; ic < n_coins; ++ic)
        {
            auto const coin =  coins[ic];
            if (m >= coin)
            {
                auto const num_coins = get_change_rec(m - coin) + 1;
                if (min_num_coins > num_coins)
                {
                    min_num_coins = num_coins;
                }
            }
        }
        min_coins[m] = min_num_coins;
    }

    return min_coins[m];
}

int get_change_dp_bottom_up(int m)
{
    min_coins[0] = 0;

    for (int im = 1; im <= m; ++im)
    {
        int min_num_coins = max_number;

        for (int ic = 0; ic < n_coins; ++ic)
        {
            if (auto const coin = coins[ic]; im>=coin)
            {
                auto const num_coins = min_coins[im - coin] + 1;

                if (num_coins < min_num_coins)
                {
                    min_num_coins = num_coins;
                }
            }
        }

        min_coins[im] =  min_num_coins;
    }

    return min_coins[m];
}

int get_change(int m)
{
    return get_change_dp_bottom_up(m);
}

int main()
{
  int m;
  cin >> m;

  int mm[(m+min_money)/min_money];
  min_coins = mm;
  memset(mm, 0, sizeof(int) *((m+min_money)/min_money));

  std::cout << get_change(m) << '\n';
}
