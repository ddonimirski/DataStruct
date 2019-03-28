#include <iostream>
#include <algorithm>
#include <numeric>
#include <memory>

using std::cout;
using std::cin;
using std::endl;

using std::accumulate;
using std::fill;

using std::make_unique;
using std::unique_ptr;

template<class T>
bool isKPartitionPossibleRec(T arr[], T subsetSum[], bool taken[], int subset, int K, int N, int curIdx, int limitIdx)
{
    if (subsetSum[curIdx] == subset)
    {
        if (curIdx == K - 2)
            return true;

        return isKPartitionPossibleRec(arr, subsetSum, taken, subset, K, N, curIdx + 1, N - 1);
    }

    for (int i = limitIdx; i >= 0; i--)
    {
        if (taken[i])
            continue;
        int tmp = subsetSum[curIdx] + arr[i];

        if (tmp <= subset)
        {
            taken[i] = true;
            subsetSum[curIdx] += arr[i];
            bool nxt = isKPartitionPossibleRec(arr, subsetSum, taken,
                    subset, K, N, curIdx, i - 1);

            taken[i] = false;
            subsetSum[curIdx] -= arr[i];
            if (nxt)
                return true;
        }
    }
    return false;
}


auto isSumDivisible(size_t sum, size_t k)
{
    return (sum%k) == 0;
}

template<class T>
bool isKPartitionPossible(T arr[], int N, int K)
{
    if (K == 1)
        return true;

    if (N < K)
        return false;

    auto const sum = accumulate(arr, arr+N, size_t{});

    if (!isSumDivisible(sum, K))
        return false;

    auto subset = sum / K;
    unique_ptr<T[]> subsetSum{new T[K]};
    fill(subsetSum.get(), subsetSum.get()+K, 0);

    unique_ptr<bool[]> taken{new bool[N]};
    fill(taken.get(), taken.get()+N, false);

    subsetSum[0] = arr[N - 1];
    taken[N - 1] = true;

    return isKPartitionPossibleRec(arr, subsetSum.get(), taken.get(), subset, K, N, 0, N - 1);
}

int main()
{
    size_t N;
    cin >> N;

    auto* const arr = new int[N];

    for (size_t i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    cout <<  isKPartitionPossible(arr, N, 3) << endl;

    delete [] arr;
}

