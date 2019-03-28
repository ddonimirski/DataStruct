#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cin;
using std::string;
using std::vector;
using std::unordered_map;
struct Query {

  string type, name;
  int number;
};

vector<Query> read_queries() {

  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    cin >> queries[i].type;
    if (queries[i].type == "add")
      cin >> queries[i].number >> queries[i].name;

    else
      cin >> queries[i].number;
  }
  return queries;
}

void write_responses(const vector<string> &result) {
  for (size_t i = 0; i < result.size(); ++i)
    std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries) {
    vector<string> result;

    unordered_map<int, string> contacts;

    for (auto const& query: queries) {

        if (query.type == "add") {
            contacts[query.number] = query.name;
        }
        else if (query.type == "del") {
            contacts.erase(query.number);
        }
        else {
            string response = "not found";
            auto found = contacts.find(query.number);
            if (found != contacts.end())
            {
                response = found->second;
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
  write_responses(process_queries(read_queries()));
  return 0;
}
