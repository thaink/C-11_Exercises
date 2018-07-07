#include <iostream>
#include <vector>
#include <algorithm>
#include "algo.h"

using namespace std;



int main()
{
    vector<int> vec={1,9, 5, 7, 2,4,5,8};
    vector<int>::iterator it = Estd::upper_bound(vec.begin(), vec.end(), 3);
    auto res = Estd::equal_range(vec.begin(), vec.end(), 9);
    cout << (res.first == res.second) << endl;
    Estd::sort(vec.begin(), vec.end());
    return 0;
}

