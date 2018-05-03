#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <functional>
#include "list_map.h"

using namespace std;

namespace test_list_map {
    using ktstd::list_map;

    void print_map (list_map<string, string>& lm)
    {
        for(auto idx = lm.begin(); idx != lm.end(); ++idx)
            cout << (*idx).first << " " << (*idx).second << "\n";
        cout << "done print map\n";
    }

    void print_map_back (list_map<string, string>& lm)
    {
        for(auto idx = lm.rbegin(); idx != lm.rend(); ++idx)
            cout << (*idx).first << " " << (*idx).second << "\n";
        cout << "done print map\n";
    }

    void print_iter(list_map<string, string>::iterator idx)
    {
        cout << "value " << (*idx).first << " " << (*idx).second << "\n";

    }

    void test()
    {
        list_map<string, string> lm;

        cout << "=================\n";
        cout << "check push_front, push_back\n";
        lm.push_front("1", "11");
        lm.push_back("2", "22");
        lm.push_front("3", "33");
        auto a =  lm.front();
        auto b =  lm.back();
        assert(a.first == "3");
        assert(b.first == "2");

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
        list_map<string, string> lm;
        cout << "=================\n";
        cout << "check count, find\n";
        lm.push_back("1", "11");
        lm.push_back("2", "22");
        lm.push_back("3", "33");
        lm.push_back("4", "44");
        assert(lm.count("0") == 0);
        assert(lm.count("1") == 1);
        auto idx = lm.find("0");
        assert(idx==lm.end());
        auto idx2 = lm.find("1");
        assert(idx2!=lm.end());
        print_iter(idx);
        print_iter(idx2);

        list_map<string, string>::const_reference ifx = lm.front();
        cout << "front " << ifx.first << " " << ifx.second << "\n";

        auto idx3 = lm.find_as("2", std::greater<string>());
        assert(idx3!=lm.end());

        assert(lm.validate() == 1);
        list_map<string, string>::const_iterator i1 = lm.begin();
        assert(lm.validate_iterator(lm.begin())==2);
        assert(lm.validate_iterator(lm.end()) == 1);
        cout << "=================\n";
        cout << "check erase\n";
        lm.erase("2");
        print_map(lm);

        lm.erase(lm.begin());
        print_map(lm);

        lm.erase(lm.rbegin());
        print_map(lm);

        lm.clear();
        print_map(lm);
    }
}

