#include <iostream>
#include "interval_map.cpp"

using namespace std;

using KM = unsigned int;
using KV = int;
void print_element(const interval_map<KM,KV>& iv)
{
    cout << "--------print-------\n";
    for (auto x:iv.m_map)
        cout << x.first << " " << x.second << "\n";
    cout << "--------done--------\n";
}

void IntervalMapTest()
{
    //test constructor and simple cases
    interval_map<KM,KV> iv(8);
    print_element(iv);
    iv.assign(7, 6, 5);
    iv.assign(6, 6, 5);
    print_element(iv);
    iv.assign(4, 6, 5);
    print_element(iv);
    iv.assign(0, 6, 5);
    print_element(iv);
    iv.assign(0, numeric_limits<KM>::max(), 8);
    print_element(iv);
    iv.assign(0, numeric_limits<KM>::lowest(), 8);
    print_element(iv);

    cout << "done testing!\n";
}

void IntervalMapTest2()
{
    interval_map<KM,KV> iv(8);
}

int main()
{
    IntervalMapTest();
    return 0;
}

