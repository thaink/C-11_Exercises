#include <iostream>
#include <algorithm>
#include <forward_list>
#include <stack>
#include <cmath>

using namespace std;

class mStack : private std::stack<std::pair<int, int>> {
    using Parent = typename std::stack<std::pair<int, int>>;
public:
    using Parent::empty;
    void push(int value) {
        if(empty())
            Parent::push(make_pair(value,value));
        else
            Parent::push(make_pair(value, std::min(Parent::top().second, value)));
    }

    void pop() {
       Parent::pop();
    }

    int top() {return Parent::top().first;}
    int min() {return Parent::top().second;}
};

int main()
{

    mStack ms;
    ms.push(5);  ms.push(6); ms.push(4); ms.push(3); ms.push(1); ms.push(7); ms.push(2);
    while (!ms.empty()) {
        cout << "(" << ms.top() << "," << ms.min() << ") ";
        ms.pop();
    }
    cout << endl;
    return 0;
}

