#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <functional>
#include "list_map.h"

using namespace std;

namespace test_iterator {
    using ktstd::list_map;

    void print_map (list_map& lm)
    {
        for(auto idx = lm.begin(); idx != lm.end(); ++idx)
            cout << (*idx).first << " " << (*idx).second << "\n";
        cout << "done print map\n";
    }

    void print_map_back (list_map& lm)
    {
        for(auto idx = lm.rbegin(); idx != lm.rend(); ++idx)
            cout << (*idx).first << " " << (*idx).second << "\n";
        cout << "done print map\n";
    }

    void print_iter(list_map::const_iterator idx)
    {
        cout << "value " << (*idx).first << " " << (*idx).first << "\n";

    }

    void test()
    {
        list_map lm;

        cout << "=================\n";
        cout << "check push_front, push_back\n";
        lm.push_front("1", "11");
        lm.push_back("2", "22");
        lm.push_front("3", "33");
        auto a =  lm.front();
        auto b =  lm.back();

        print_map(lm);
        print_map_back(lm);

        cout << "=================\n";
        cout << "check pop_front, pop_back\n";
        lm.pop_front();
        print_map(lm);
        lm.pop_back();
        print_map_back(lm);
        lm.pop_back();
        print_map(lm);
    }

    void test2()
    {
        list_map lm;
        cout << "=================\n";
        cout << "check count, find\n";
        lm.push_back("1", "11");
        lm.push_back("2", "22");
        lm.push_back("3", "33");
        lm.push_back("4", "44");
        cout << "count 0 " << lm.count("0") << "\n";
        cout << "count 1 " << lm.count("1") << "\n";
        auto idx = lm.find("0");
        assert(idx==lm.end());
        auto idx2 = lm.find("1");
        assert(idx2!=lm.end());
        print_iter(idx);
        print_iter(idx2);

        list_map::const_reference ifx = lm.front();
        cout << "front " << ifx.first << " " << ifx.second << "\n";

        auto idx3 = lm.find_as("2", std::greater<string>());
        assert(idx3!=lm.end());

        cout << "validate " << lm.validate() << "\n";
        cout << "validate " << lm.validate_iterator(lm.begin()) << "\n";
        cout << "validate " << lm.validate_iterator(lm.end()) << "\n";
        cout << "=================\n";
        cout << "check count, find\n";
        lm.erase("2");
        print_map(lm);

        lm.erase(lm.begin());
        print_map(lm);

        lm.erase(lm.rbegin());
        print_map(lm);

        lm.clear();
        print_map(lm);
    }

    void test3()
    {

    }

}

int main()
{
    test_iterator::test();
    test_iterator::test2();
    return 0;
}

