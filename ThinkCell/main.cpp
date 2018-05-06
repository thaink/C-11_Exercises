#include <iostream>
#include <random>
#include "interval_map.cpp"

using namespace std;

using KM = int8_t;
using KV = int8_t;

//void test_map_validate(const interval_map<KM,KV>& iv)
//{
//    cout << "------------start validated--------\n";
//    for (auto it = iv.m_map.begin(); it != --iv.m_map.end();++it)
//    {
//        auto it2(it); ++it2;
//        cout << "K,V: " << (int)it->first << " " << (int)it->second << " K,V: " << (int)it2->first << " " << (int)it2->second << "\n";
//        if(!(it->first < (it2)->first))
//            std::cerr << "map order broken\n";

//        if((it->second == it2->second))
//            std::cerr << "map duplicate value exist\n";
//    }

//    cout << "---------successful validated--------\n";
//}

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
    iv.assign_and_print(7, 6, 8);
    iv.assign_and_print(6, 6, 5);
    iv.assign_and_print(4, 6, 8);
    iv.assign_and_print(1, 6, 5);
    iv.assign_and_print(1, numeric_limits<KM>::max(), 8);
    iv.assign_and_print(numeric_limits<KM>::lowest(),6, 5);
    iv.assign_and_print(3, numeric_limits<KM>::max(), 45);
    iv.assign_and_print(1, 6, 43);
    iv.assign_and_print(5, 10, 67);
    iv.assign_and_print(10, 25, 57);
    //test_map_validate(iv);

    cout << "done testing!\n";
}

void IntervalMapTest_random()
{
    interval_map<KM,KV> iv(8);
    int MAX = 20000000;
    std::default_random_engine generator;
    std::uniform_int_distribution<KM> distribution(numeric_limits<KM>::lowest(),numeric_limits<KM>::max());

    std::default_random_engine generator2;
    std::uniform_int_distribution<KV> distribution2(numeric_limits<KV>::lowest(),numeric_limits<KV>::max());

    for (int i = 1; i < MAX; ++i) {
        KM dbegin = distribution(generator);
        KM dend   = distribution(generator);
        KV val    = distribution2(generator2);
        iv.assign_and_print(dbegin,dend,val);
    }
    //test_map_validate(iv);
}

int main()
{
    //IntervalMapTest();
    IntervalMapTest_random();;
    return 0;
}

