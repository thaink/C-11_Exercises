#include <iostream>
#include "vector_map.h"

using namespace std;

namespace test_vector_map {
    using ktstd::vector_map;

    void print_element(const vector_map::value_type& x)
    {
        cout << "element " << x.first << " " << x.second << "\n";
    }

    void print_map(const vector_map& vm)
    {
        for(auto x:vm)
            print_element(x);
        cout << "------done print map----\n";
    }

    void test()
    {
        using map_value_t = std::pair<string,string>;
        using map_compare_t = std::less<string>;
        allocator<map_value_t> alloc;
        map_compare_t comp;

        vector_map va;
        cout << "\n=================\n";
        cout << "test base_type functions\n";
        cout << "size " << va.size() << "\n";

        cout << "\n=================\n";
        cout << "test constructor\n";
        vector_map va_temp = vector_map(alloc);
        vector_map va_temp2(comp,alloc);
        vector_map va_temp3(comp,alloc);
        cout << "size " << va_temp.size() << "\n";
        cout << "size " << va_temp2.size() << "\n";
        cout << "size " << va_temp3.size() << "\n";
        vector_map va2 = {{"1", "11"}, {"2","22"}};
        print_map(va2);


        cout << "\n=================\n";
        cout << "test base_type functions\n";

    }
}

int main()
{
    test_vector_map::test();
    return 0;
}

