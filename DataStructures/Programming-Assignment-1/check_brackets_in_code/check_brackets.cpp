#include <iostream>
#include <stack>
#include <string>

using std::cout;
using std::endl;

struct Bracket
{
    Bracket(char type, size_t position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    size_t position;

    friend std::ostream& operator << (std::ostream& os, Bracket const& b)
    {
        return os << b.type << ' ' << b.position;
    }
};

int main()
{ std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;


    for (size_t position = 0; position < text.length(); ++position)
    {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{')
        {
            opening_brackets_stack.push(Bracket{next, position+1});
        }
        else if (next == ')' || next == ']' || next == '}')
        {
            if (opening_brackets_stack.size() == 0)
            {
                opening_brackets_stack.push(Bracket{next, position+1});
               break;
            }

            auto top = opening_brackets_stack.top();

            if (top.Matchc(next))
            {
                opening_brackets_stack.pop();
            }
            else
            {

                opening_brackets_stack.push(Bracket{next, position+1});
                break;
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.size() == 0)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << opening_brackets_stack.top().position << endl;
    }

    return 0;
}
