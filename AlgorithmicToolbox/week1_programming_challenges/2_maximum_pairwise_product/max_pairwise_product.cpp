#include <iostream>
#include <vector>
#include <cstdio>

using std::vector;
using std::cin;
using std::cout;

using type_t = int64_t;
using numbers_t = std::vector<int>;


type_t MaxPairwiseProduct(const numbers_t& nums)
{
#if 1
    auto const n = nums.size();
    if (n < 2)
        return 0u;

    int max_id1 = 0, max_id2 = 1;

    if (nums[max_id1] < nums[max_id2])
    {
        auto const tmp = max_id1;
        max_id1 = max_id2;
        max_id2 = tmp;
    }

    for (uint64_t i = 2; i < n; ++i)
    {
        if (nums[max_id1] < nums[i])
        {
            max_id2 = max_id1;
            max_id1 = i;
        }

        else if (nums[max_id2] < nums[i])
        {
            max_id2 = i;
        }
    }

    type_t res = nums[max_id2];
    res *= nums[max_id1];

    return res;
#else
    int n = nums.size();

    int max_index1 = -1;
    for (int i = 0; i < n; ++i)
        if ((max_index1 == -1) || (nums[i] > nums[max_index1]))
            max_index1 = i;

    int max_index2 = -1;
    for (int j = 0; j < n; ++j)
        if ((j != max_index1) && ((max_index2 == -1) || (nums[j] > nums[max_index2])))
            max_index2 = j;

    return ((type_t) (nums[max_index1])) * nums[max_index2];
#endif
}

#if defined STRESS_TESTS
#include <algorithm>

type_t max_prod(numbers_t const& nums)
{
#if 0
    auto const n = nums.size();
    if (n < 2)
        return 0u;

    auto result = nums[0] * nums[1];

    for (uint64_t i = 0; i<n; ++i)
    {
        for (uint64_t j = i+1; j<n; ++j)
        {
            if (nums[i] != nums[j])
            {
                auto res = nums[i];
                res *= nums[j];
                if (result < res)
                    result = res;
            }
        }
    }

    return result;
#elif 0
    numbers_t v{nums};

    std::sort(v.begin(), v.end());

    int i = v.size();
    type_t r = v[--i];
    r *= v[--i];

    return r;
#else

    int n = nums.size();

    int max_index1 = -1;
    for (int i = 0; i < n; ++i)
        if ((max_index1 == -1) || (nums[i] > nums[max_index1]))
            max_index1 = i;

    int max_index2 = -1;
    for (int j = 0; j < n; ++j)
        if ((j != max_index1) && ((max_index2 == -1) || (nums[j] > nums[max_index2])))
            max_index2 = j;

    return ((type_t) (nums[max_index1])) * nums[max_index2];
#endif
}

template<class T>
void pr(T const& c, std::ostream& os = std::cerr)
{
    os << '{';
    auto n = c.size();
    for (auto const& v: c)
    {
        os << v << (--n?", ":"}\n");
    }
}

#include <random>

int main()
{
    int N = 100000;
    int M = 1900000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2,N);

    for (int t = 0; t < 1; ++t)
    {
        auto n = dis(gen);
        numbers_t nums(n);

        for (int i = 0; i < 30; ++i)
        {
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(2,M);

            for (auto& v: nums)
            {
                v = dis(gen);
            }

            auto r1 = max_prod(nums);
            auto r2 = MaxPairwiseProduct(nums);


            if (r1!=r2)
            {
                cout << r1 << " " << r2 << "->" << (r1 == r2) << std::endl;
                pr(nums);
            }

        }
    }

}

#else

int main() {

    std::ios::sync_with_stdio(false);

    uint64_t n;
    cin >> n;
    numbers_t numbers(n);
    for (uint64_t i = 0u; i < n; ++i) {
        cin >> numbers[i];
    }

    auto result = MaxPairwiseProduct(numbers);
    cout << result << "\n";
    return 0;
}
#endif
