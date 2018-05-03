#include <iostream>
#include "array.h"

using namespace std;

namespace test_array
{
    using ktstd::array;

    void print_arr(array<int,10>& a)
    {
        for(auto x = a.begin(); x!= a.cend(); ++x)
            cout << *x << " ";
        cout << "\n=end print=========\n";
    }

    void print_arr_back(array<int,10>& a)
    {
        for(auto idx = a.rbegin(); idx != a.rend(); ++idx)
            cout << *idx << " ";
        cout << "\n=end print=========\n";
    }

    void test() {
        array<int,10> arr;
        std::cout << "N " << arr.count << "\n";

        cout << "\n=================\n";
        cout << "test iterator\n";
        arr.fill(5);
        print_arr(arr);
        print_arr_back(arr);
        cout << "front " << arr.front() << "\n";
        cout << "back " << arr.back() << "\n";
        cout << "empty " << arr.empty() << "\n";
        cout << "size " << arr.size() << "\n";
        cout << "maxsize " << arr.max_size() << "\n";
        int* ad = arr.data();
        for (int i=0; i<10; i++)
            cout << *(ad++) << " ";
        cout << "\n";

        cout << "\n=================\n";
        cout << "test swap...\n";
        array<int,10> brr;
        brr.fill(6);
        arr.swap(brr);
        print_arr(arr);
        print_arr(brr);
        ktstd::swap(arr,brr);
        print_arr(arr);
        print_arr(brr);
        cout << "\n=================\n";
        cout << "test ACCESS...\n";
        arr[3] = 10;
        arr[6] = 9;
        print_arr(arr);
        cout << "a==b " << (arr==brr) << "\n";
        cout << "a!=b " << (arr!=brr) << "\n";
        cout << "a<b " << (arr<brr) << "\n";
        cout << "a<=b " << (arr<=brr) << "\n";
        cout << "a>b " << (arr>brr) << "\n";
        cout << "a>=b " << (arr>=brr) << "\n";
    }
}

