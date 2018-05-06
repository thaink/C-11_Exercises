#include <iostream>
#include "interval_map.cpp"

using namespace std;

using KM = unsigned int;
using KV = int;

void test_map_validate(const interval_map<KM,KV>& iv)
{
    cout << "------------start validated--------\n";
    for (auto it = iv.m_map.begin(); it != --iv.m_map.end();++it)
    {
        auto it2(it); ++it2;
        cout << "K,V: " << it->first << " " << it->second << " K,V: " << it2->first << " " << it2->second << "\n";
        if(!(it->first < (it2)->first))
            std::cerr << "map order broken\n";

        if((it->second == it2->second))
            std::cerr << "map duplicate value exist\n";
    }

    cout << "---------successful validated--------\n";
}

//void print_element(const interval_map<KM,KV>& iv)
//{
//    cout << "--------print-------\n";
//    for (auto x:iv.m_map)
//        cout << x.first << " " << x.second << "\n";
//    cout << "--------done--------\n";
//}

void IntervalMapTest()
{
    //test constructor and simple cases
    interval_map<KM,KV> iv(8);
    iv.assign(7, 6, 5);
    iv.assign(6, 6, 5);
    iv.assign(4, 6, 5);
    iv.assign(0, 6, 5);
    iv.assign(0, numeric_limits<KM>::max(), 8);
    iv.assign(numeric_limits<KM>::lowest(),6, 5);
    iv.assign(3, numeric_limits<KM>::max(), 45);
    iv.assign(0, 6, 43);
    iv.assign(5, 10, 67);
    iv.assign(10, 25, 57);
    test_map_validate(iv);

    cout << "done testing!\n";
}

void IntervalMapTest_random()
{
    interval_map<KM,KV> iv(8);
}

int main()
{
    IntervalMapTest();
    return 0;
}

