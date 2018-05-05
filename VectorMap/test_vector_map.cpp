#include <iostream>
#include "vector_map.h"

using namespace std;

namespace test_vector_map {
    using ktstd::vector_map;

    void print_element(const vector_map::value_type& x)
    {
        cout << "element " << x.first << " " << x.second << "\n";
    }

    void print_map(const vector_map& vm, string name = string())
    {
        cout << "------print "<< name << "----\n";
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
        cout << "size " << va_temp.size() << "\n";
        cout << "size " << va_temp2.size() << "\n";

        vector_map va2 = {{"1", "11"}, {"2","22"}};
        print_map(va2,"va2");
        vector_map va_temp3(va2);
        cout << "size " << va_temp3.size() << "\n";
        vector_map va_temp4(std::move(va_temp3));
        cout << "size " << va_temp3.size() << "\n";
        cout << "size " << va_temp4.size() << "\n";

        vector_map va_temp5(std::move(va_temp4), alloc);
        cout << "size " << va_temp4.size() << "\n";
        cout << "size " << va_temp5.size() << "\n";

        vector_map va3({{"3", "11"}, {"4","22"}},comp,alloc);
        print_map(va3, "va3");

        vector_map va4(va3.begin(), va3.end());
        print_map(va4, "va5");

        vector_map va5(va3.begin(), va3.end(), comp);
        print_map(va5, "va5");

        vector_map va_temp6;
        va_temp6 = va2;
        print_map(va_temp6, "va_temp6");

        vector_map va_temp7;
        va_temp7 = {{"5", "11"}, {"6","22"}};
        print_map(va_temp7, "va_temp7");

        vector_map va_temp8;
        va_temp8 = std::move(va_temp6);
        cout << "size " << va_temp6.size() << "\n";
        cout << "size " << va_temp8.size() << "\n";

        cout << "\n=================\n";
        cout << "test base_type functions\n";
        va_temp7.swap(va_temp8);
        print_map(va_temp7, "va_temp7");
        print_map(va_temp8, "va_temp8");

        vector_map::iterator x = va_temp7.begin();
        (*x).first = "7";
        (*x).second="77";
    }
}

