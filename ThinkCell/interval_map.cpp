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

//        if(m_map.size() == 1) { //map is just constructed
//            if(val == m_map.begin()->second) return;
//            if(keyEnd < std::numeric_limits<K>::max())
//                m_map.emplace_hint(m_map.end(), keyEnd, m_map.begin()->second);

//            if(std::numeric_limits<K>::lowest() < keyBegin)
//                m_map.emplace_hint(++(m_map.begin()), keyBegin, val);
//            else
//                m_map.begin()->second = val;

//            return;
//        }

        /*
         * Complexity analysis:
         * - Two lower_bound() method takes two O(logN)
         * - The erase() is log(N) where N is number of positions need to be deleted
         * - Other method take O(1)
         * - For operator on K and V
         *      - for V, use only two operator == (one for keyBegin and one for keyEnd)
         *      - for K, excluding comparision inside lower_bound, use only two operator < (one for keyBegin and one for keyEnd)
         */
        using map_type      = std::map<K,V>;
        using iterator      = typename map_type::iterator;
        using iterator_pair = std::pair<iterator,iterator>;

        //insert or replace at keyBegin
        //iterator itEndLB   = m_map.lower_bound(keyEnd);
//        iterator_pair itEndER  = m_map.equal_range(keyEnd);
//        iterator iEndLB(itEndER.first);
//        V  previousVal = (--(itEndER.second))->second;
//        if(keyEnd < std::numeric_limits<K>::max()) {
//            if(itEndER.first == m_map.end()) {
//                if(!(val == m_map.rbegin()->second))
//                    iEndLB = m_map.emplace_hint(itEndER.first, keyEnd,  m_map.rbegin()->second);
//            } else {
//                if ((keyEnd < itEndLB->first) && (!(val == (--itEndLB)->second)))
//                       itEndLB = m_map.emplace_hint(itEndLB, keyEnd, (--itEndLB)->second);
//            }
//        }

        iterator itEndLB = m_map.lower_bound(keyEnd);
        iterator itEnd(itEndLB);
        if(keyEnd < std::numeric_limits<K>::max()) {
            itEnd = m_map.emplace_hint(itEndLB, keyEnd, (--itEndLB)->second);
            //iterator temp(itEnd);
            //++temp;
            K elb = itEndLB->first;
            K ebn = itEnd->first;
            //itEndLB now point to the previous point of itEnd
            ///if((temp != m_map.end()) && (itEnd->second == temp->second))
            if(itEnd->second == val)
                ++itEnd; //duplicated value. advance to delete
        }

        iterator itBeginLB = m_map.lower_bound(keyBegin);
        iterator itBegin;
        //following if should be replaced by insert_or_assign
        if(keyBegin < itBeginLB->first) {
            itBegin = m_map.emplace_hint(itBeginLB, keyBegin, val);
            --itBeginLB;
        } else {
            itBegin = itBeginLB;
            itBegin->second = val;
        }
        //after this itBegin==itBeginLB


        if(std::numeric_limits<K>::lowest() < keyBegin) {
            --itBeginLB;//now point to previous point of itBegin
            K elb = itBeginLB->first;
            K ebn = itBegin->first;
            if(itBegin->second == itBeginLB->second)
                --itBegin;//move back to delete
        }




//        K ek = itEndLB->first;
//        //insert or replace at keyBegin
//        iterator itBeginLB = m_map.lower_bound(keyBegin);//itBeginLB != end() because we already insert keyEnd if necessary
//        if(keyBegin < (*itBeginLB).first) {
//            if(!(val == (--itBeginLB)->second))
//                itBeginLB = m_map.emplace_hint(itBeginLB, keyBegin, val);
//        } else { //replace current value
//            if(!(val == (--itBeginLB)->second))
//                (*itBeginLB).second = val;
//        }

        //check if whatever we did to begin. end does not change
//        K ek2 = itEndLB->first;
//        assert(ek == itEndLB->first);
        //erase middle node between begin and end
        if(itBegin != itEnd) {
            K eb = itBegin->first;
            K ee = (itEnd == m_map.end()) ? K() : itEnd->first;
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
        std::cout << "------------start validated  "<<  (int)m_map.size()  <<"--------\n";
        print_element();
        for (auto it = m_map.begin(); it != --m_map.end();++it)
        {
            auto it2(it); ++it2;
            //std::cout << "K,V: " << (int)it->first << " " << (int)it->second << " K,V: " << (int)it2->first << " " << (int)it2->second << "\n";
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
