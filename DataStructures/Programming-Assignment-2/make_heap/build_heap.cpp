#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder
{
    private:
        vector<int64_t> data_;
        vector< pair<size_t, size_t> > swaps_;

        void WriteResponse() const
        {
            cout << swaps_.size() << "\n";
            for (size_t i = 0; i < swaps_.size(); ++i)
            {
                cout << swaps_[i].first << " " << swaps_[i].second << "\n";
            }
        }

        void ReadData()
        {
            int n;
            cin >> n;
            data_.resize(n);

            for(int i = 0; i < n; ++i)
            {
                cin >> data_[i];
            }
        }

        void shift_down(size_t id)
        {
            auto const mid = id;
            auto const size = data_.size();
            auto const di = 2 * mid;
            auto const l_id = di + 1;

            if (l_id < size && data_[l_id] < data_[id])
            {
                id = l_id;
            }

            auto const r_id = di + 2;
            if (r_id < size && data_[r_id] < data_[id])
            {
                id = r_id;
            }

            if (mid != id)
            {
                swaps_.push_back(make_pair(mid, id));
                swap(data_[id], data_[mid]);
                shift_down(id);
            }
        }

        void GenerateSwaps()
        {
            swaps_.clear();
            // The following naive implementation just sorts 
            // the given sequence using selection sort algorithm
            // and saves the resulting sequence of swaps.
            // This turns the given array into a heap, 
            // but in the worst case gives a quadratic number of swaps.
            //
            // TODO: replace by a more efficient implementation
#if 0
            auto const size = data_.size();
            auto const size_half = size;

            for (auto pid = size_half; pid > 0; )
            {
                shift_down(--pid);
            }
#else

            auto const size = data_.size();
            auto const size_half = data_.size();

            for (auto pid = size_half; pid > 0; )
            {
                auto mid = --pid;
                auto id = mid;

                while(id < size_half)
                {
                    auto const di = 2 * mid;
                    auto const l_id = di + 1;

                    if (l_id < size && data_[l_id] < data_[id])
                    {
                        id = l_id;
                    }

                    auto const r_id = di + 2;
                    if (r_id < size && data_[r_id] < data_[id])
                    {
                        id = r_id;
                    }

                    if (mid != id)
                    {
                        swaps_.push_back(make_pair(mid, id));
                        swap(data_[id], data_[mid]);
                        mid = id;
                    }
                    else
                    {
                        break;
                    }
                }

            }
#endif
        }

    public:
        void Solve()
        {
            ReadData();
            GenerateSwaps();
            WriteResponse();
        }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
