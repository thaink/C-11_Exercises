#include <iostream>
#include "vector_map.h"

using namespace std;

namespace test_vector_map {
    using ktstd::vector_map;

    void test()
    {
        vector_map va;
        cout << "\n=================\n";
        cout << "test base_type functions\n";
        cout << "size " << va.size() << "\n";
    }
}

int main()
{
    test_vector_map::test();
    return 0;
}

