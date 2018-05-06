#include <iostream>
#include "interval_map.cpp"

using namespace std;

using KM = unsigned int;
using KV = int;
void print_element(const interval_map<KM,KV>& iv)
{
    cout << "--------------------\n";
    for (auto x:iv.m_map)
        cout << x.first << " " << x.second << "\n";
    cout << "--------done--------\n";
}

void IntervalMapTest()
{
    interval_map<KM,KV> iv(8);
    print_element(iv);
    iv.assign(4, 6, 5);
    print_element(iv);

    cout << "done testing!\n";
}

int main()
{
    IntervalMapTest();
    return 0;
}

