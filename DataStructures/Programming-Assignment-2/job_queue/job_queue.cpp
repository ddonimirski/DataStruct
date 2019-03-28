#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::tuple;
using std::make_tuple;
using std::priority_queue;

using thread = std::tuple<size_t, int64_t>; // <id, next_free_time

static inline constexpr auto get_id(thread const& t)
{
    return std::get<0>(t);
}

static inline constexpr auto get_next_free_time(thread const& t)
{
    return std::get<1>(t);
}

struct comp_thread
{
    constexpr bool operator ()(thread const& t1, thread const& t2)
    {
        if (get_next_free_time(t1) != get_next_free_time(t2))
        {
            return get_next_free_time(t1) > get_next_free_time(t2);
        }

        return get_id(t1) > get_id(t2);
    }
};

std::ostream& operator << (std::ostream& os, thread const& t)
{
    return os  << "{" << get_id(t) << ", " << get_next_free_time(t) << "}";
}

class JobQueue
{
    private:
        size_t num_workers_;
        vector<int> jobs_;

        vector<int> assigned_workers_;
        vector<long long> start_times_;

        void WriteResponse() const
        {
            for (size_t i = 0; i < jobs_.size(); ++i)
            {
                cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
            }
        }

        void ReadData()
        {
            int m;
            cin >> num_workers_ >> m;
            jobs_.resize(m);
            for(int i = 0; i < m; ++i)
                cin >> jobs_[i];
        }

        void AssignJobs()
        {
            // TODO: replace this code with a faster algorithm.
            assigned_workers_.resize(jobs_.size());
            start_times_.resize(jobs_.size());
#if 0
            assigned_workers_.resize(jobs_.size());
            start_times_.resize(jobs_.size());
            vector<long long> next_free_time(num_workers_, 0);

            for (int i = 0; i < jobs_.size(); ++i)
            {
                int duration = jobs_[i];
                int next_worker = 0;

                for (int j = 0; j < num_workers_; ++j)
                {
                    if (next_free_time[j] < next_free_time[next_worker])
                        next_worker = j;
                }
                assigned_workers_[i] = next_worker;
                start_times_[i] = next_free_time[next_worker];
                next_free_time[next_worker] += duration;
            }
#else
            priority_queue<thread, vector<thread>, comp_thread> q;

            for (size_t i = 0; i < num_workers_; ++i)
            {
                auto const tup = make_tuple<int, int64_t>(size_t{i}, 0l);
                q.push(tup);
            }

            for (size_t i = 0; i < jobs_.size(); ++i)
            {
                auto const duration = jobs_[i];

                size_t id;
                int64_t next_free_time;

                std::tie(id, next_free_time) = q.top();
                q.pop();

                assigned_workers_[i] = id;
                start_times_[i] = next_free_time;

                next_free_time += duration; // next time

                auto const tup  = make_tuple(id, next_free_time);
                q.push(tup);
            }
#endif
        }

    public:
        void Solve()
        {
            ReadData();
            AssignJobs();
            WriteResponse();
        }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
