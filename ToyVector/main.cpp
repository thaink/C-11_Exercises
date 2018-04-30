#include <iostream>
#include "vector.h"
#include <assert.h>
#include <algorithm>

using namespace std;

int main()
{
    //simple test initialize + size
    Estd::vector<int> v1(10,5);
    assert(v1.size()==10);
    assert(*(v1.begin())==5);
    assert(*(v1.begin()+9)==5);

    //test copy constructor
    Estd::vector<int> v2(v1);
    assert(v2.size()==10);
    assert(*(v2.begin())==5);
    assert(*(v2.begin()+9)==5);

    //test copy assignment
    Estd::vector<int> v3(2);
    Estd::vector<int> v4(20);
    v4=v1;
    assert(v4.size()==10);
    assert(v4.capability()==20);
    assert(*(v4.begin())==5);
    assert(*(v4.begin()+9)==5);

    v3 = v1;
    assert(v3.size()==10);
    assert(v3.capability()==10);
    assert(*(v3.begin())==5);
    assert(*(v3.begin()+9)==5);

    //test move assignment
    Estd::vector<int> v5=std::move(v3);
    assert(v5.size()==10);
    assert(v5.capability()==10);
    assert(*(v5.begin())==5);
    assert(*(v5.begin()+9)==5);
    assert(v3.size()==0);
    assert(v3.capability()==0);

    Estd::vector<int> v6=std::move(v4);
    assert(v6.size()==10);
    assert(v6.capability()==20);
    assert(*(v6.begin())==5);
    assert(*(v6.begin()+9)==5);
    assert(v4.size()==0);
    assert(v4.capability()==0);

    //test
    Estd::vector<int> v7(0);
    assert(v7.size()==0);
    assert(v7.capability()==0);
    v7.reserve(20);
    assert(v7.size()==0);
    assert(v7.capability()==20);
    v6.reserve(10);
    assert(v6.size()==10);
    assert(v6.capability()==20);
    v6.reserve(40);
    assert(v6.size()==10);
    assert(v6.capability()==40);
    assert(*(v6.begin())==5);
    assert(*(v6.begin()+9)==5);

    v6.push_back(8);
    v6.push_back(9);
    assert(*(v6.begin()+9)==5);
    assert(*(v6.begin()+10)==8);
    assert(*(v6.begin()+11)==9);
    assert(v6.size()==12);
    assert(v6.capability()==40);

    int s = accumulate(v6.begin(),v6.end(),0);
    cout << s << endl;
    return 0;
}


