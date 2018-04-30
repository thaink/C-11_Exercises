#include <iostream>
#include "vector.h"
#include "vector.cpp"

using namespace Estd;

int main()
{
    struct MInt {
        int x;
    };



    Estd::vector<int> v1(5);
    v1.push_back(4);
    std::cout << "Hello World!" << std::endl;
    return 0;
}

