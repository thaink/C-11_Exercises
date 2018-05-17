#include <assert.h>
#include <map>
#include <limits>
#include <iostream>

template<class K, class V>
class interval_map {
    friend void IntervalMapTest();

public:
    std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.begin(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }
protected:

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        //checking for simple cases
        if(!(keyBegin < keyEnd))
            return;

        /*
         * Complexity analysis:
         * - Two lower_bound() method takes two O(logN)
         * - The erase() is log(N) where N is number of positions need to be deleted
         *   This is unavoidable since we have to remove duplicated nodes.
         * - Other method take O(1)
         */
        using map_type      = std::map<K,V>;
        using iterator      = typename map_type::iterator;

        //insert keyEnd first
        iterator itEndLB = m_map.lower_bound(keyEnd);
        iterator itEnd(itEndLB);
        --itEndLB;//to previous node
        if(keyEnd < itEndLB->first) {
            if(!(itEndLB->second == val))
                itEnd = m_map.emplace_hint(itEndLB, keyEnd, (itEndLB)->second);
        } else {
            if(itEndLB->second == val)
                ++itEnd;

        }
//        iterator itEnd = m_map.emplace_hint(itEndLB, keyEnd, (--itEndLB)->second);
//        if(itEnd->second == val)
//            ++itEnd; //duplicated value. advance to delete

        //now insert keyBegin
        iterator itBeginLB = m_map.lower_bound(keyBegin);
        iterator itBegin(itBeginLB);
        //following if should be replaced by insert_or_assign
        //unfortunately, my compiler yield not found error on this function
        if(keyBegin < itBeginLB->first) {
            --itBeginLB;//move back to previous node
            if(!(val == itBeginLB->second))
                itBegin = m_map.emplace_hint(itBeginLB, keyBegin, val);
            else
                --itBegin;

        } else {
            itBegin->second = val;
            if(itBegin != m_map.begin()) {
                --itBeginLB;//itBeginLB now point to previous point of itBegin
                if(val == itBeginLB->second)
                    --itBegin;//move back to delete
            }
        }


//        if(itBegin != m_map.begin()) {//std::numeric_limits<K>::lowest() < keyBegin
//            --itBeginLB;//itBeginLB now point to previous point of itBegin
//            if(itBegin->second == itBeginLB->second)
//                --itBegin;//move back to delete
//        }

        //erase middle node between begin and end
        if(itBegin != itEnd) {
            m_map.erase(++itBegin, itEnd);
        }

    }
public:

     void assign_and_print( K const& keyBegin, K const& keyEnd, V const& val ) {
        std::cout << "---insert--- " << (int)keyBegin << " " << (int)keyEnd << " " << (int)val << "\n";
        if(!(keyBegin < keyEnd))
            return;
        assign(keyBegin, keyEnd, val);
        test_map_validate();
     }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }

    void print_element()
    {
        //std::cout << "--------print-------\n";
        for (auto x:m_map)
            std::cout << (int)x.first << " " << (int)x.second << "\n";
        //::cout << "--------done--------\n";
    }

    void test_map_validate()
    {
        std::cout << "------------start validated  "<<  m_map.size()  <<"--------\n";
        print_element();
        for (auto it = m_map.begin(); it != --m_map.end();++it)
        {
            auto it2(it); ++it2;
            if(!(it->first < (it2)->first))
                throw std::invalid_argument("map order broken\n");

            if((it->second == it2->second))
                throw std::invalid_argument("map duplicate value exist\n");
        }

        std::cout << "---------successful validated--------\n";
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.
