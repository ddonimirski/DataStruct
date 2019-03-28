#include <iostream>
#include <queue>
#include <vector>

template<class T>
void prc(T const& cont)
{
    for (auto const& v: cont)
    {
        std::cerr << v << ' ';
    }
}

#if 0
#define PRV(v) do { std::cerr << __FUNCTION__ << ':' << __LINE__ << ':' << '(' << #v << ')' << (v) << std::endl; } while(0)
#define PRC(c) do { std::cerr << __FUNCTION__ << ':' << __LINE__ << ':' << '(' << #c << ')'; prc(c); std::cerr << std::endl; } while(0)
#define PRI(v) do { std::cerr << __FUNCTION__ << ':' << __LINE__ << ':' << (v) << std::endl; } while(0)
#define PRT(t) do { std::cerr << t; } while(0)
#else
#define PRV(v) do {} while(0)
#define PRC(c) do {} while(0)
#define PRI(v) do {} while(0)
#define PRT(t) do {} while(0)
#endif

struct Request
{
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;

    friend std::ostream& operator << (std::ostream& os, Request const& req)
    {
        return os << '(' << req.arrival_time << ',' << req.process_time << ')';
    }
};

struct Response
{
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer
{
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {
        PRV(size_);
    }

    Response Process(const Request &request)
    {
        PRV(request);
        PRV(finish_time_.front());
        PRV(finish_time_.size());
        // write your code here

        while (!finish_time_.empty() && finish_time_.front() <= request.arrival_time)
        {
            PRV(finish_time_.front());
            PRT("was removed the queue\n");
            finish_time_.pop();
        }

        PRV(finish_time_.size());
        PRV(size_);

        if (size_ == finish_time_.size())
        {
            return  { true, -1 };
        }

        auto const current_start_time = finish_time_.empty()
            ? request.arrival_time
            :finish_time_.back();

        PRV(current_start_time);
        PRV(current_start_time + request.process_time);

        finish_time_.push(current_start_time + request.process_time);

        return { false, current_start_time };

    }

private:
    size_t size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector<Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer)
{
    std::vector <Response> responses;
    for (size_t i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses)
{
    for (size_t i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main()
{
    PRT("--------------------begin-----------------\n");
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    PRT("--------------------end-------------------\n");
    return 0;
}
