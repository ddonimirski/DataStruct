#include <iostream>
#include <string>
#include <vector>
#include <ios>

using std::string;
using hash_t = unsigned long long;
using std::cerr;
using std::endl;
using std::hex;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

template<class CONT>
void print_occurrences(const CONT& output)
{
    for (auto const& e: output)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";
}


namespace {
    hash_t pow_mul = 1;
    const hash_t multiplier = 2;
    const hash_t prime = 1; //1000000007;
}

hash_t hash_str(const string& pat)
{
    hash_t hash = 0;
    pow_mul = 1;
    hash_t n = 0;

    for (auto const e: pat)
    {
        pow_mul *= multiplier;
        hash = (hash * multiplier + e) % prime;
    }

    return hash;
}

hash_t hash_next(const string& text, hash_t prev, size_t idb, size_t ide)
{
    if (idb == 0)
    {
        hash_t hash = 0;

        for (;idb < ide; ++idb )
        {
            hash = (hash * multiplier + text[idb]) % prime;
        }

        return hash;
    }

    else
    {
        return (prev*multiplier - text[idb-1] * pow_mul + text[ide-1]) %prime;
    }
}


std::vector<int> get_occurrences(const Data& input)
{
    auto const& p = input.pattern;
    auto const& t = input.text;
    std::vector<int> ans;

    auto const hash_pat = hash_str(p); 
    auto hash_text = 0;

    for (auto b = 0ull, e = b + p.size(); e <= t.size(); ++b, ++e)
    {
        hash_text = hash_next(t, hash_text, b, e);

        if (hash_pat != hash_text)
        {
            continue;
        }

        if (t.substr(b, p.size()) == p)
        {
            ans.push_back(b);
        }
    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
