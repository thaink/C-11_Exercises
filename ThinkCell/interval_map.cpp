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

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        std::cout << "---insert--- " << keyBegin << " " << keyEnd << " " << val << "\n";
        //checking for simple cases
        if(!(keyBegin < keyEnd))
                return;

        if((m_map.size() == 1) && !(val == m_map.begin()->second)) { //map is just constructed
            if(keyEnd < std::numeric_limits<K>::max())
                m_map.emplace_hint(m_map.end(), keyEnd, m_map.begin()->second);

            if(std::numeric_limits<K>::lowest() < keyBegin)
                m_map.emplace_hint(m_map.begin(), keyBegin, val);
            return;
        }

        /*
         * Complexity analysis:
         * - Two lower_bound() method takes two O(logN)
         * - The erase() is log(N) where N is number of positions need to be deleted
         * - Other method take O(1)
         * - For operator on K and V
         *      - for V, use only two operator == (one for keyBegin and one for keyEnd)
         *      - for K, excluding comparision inside lower_bound, use only two operator < (one for keyBegin and one for keyEnd)
         */
        using map_type = std::map<K,V>;
        using iterator = typename map_type::iterator;

        //insert or replace at keyBegin
        iterator itEndLB   = m_map.lower_bound(keyEnd);
        if(itEndLB == m_map.end()) {
            if((keyEnd < std::numeric_limits<K>::max()) && !(val == m_map.rbegin()->second))
                itEndLB = m_map.emplace_hint(itEndLB, keyEnd,  m_map.rbegin()->second);
        } else {
            if ((keyEnd < itEndLB->first) && (!(val == (--itEndLB)->second)))
                   itEndLB = m_map.emplace_hint(itEndLB, keyEnd, (--itEndLB)->second);
        }

        //insert or replace at keyBegin
        iterator itBeginLB = m_map.lower_bound(keyBegin);//itBeginLB != end() because we already insert keyEnd if necessary
        if(keyBegin < (*itBeginLB).first) {
            if(!(val == (--itBeginLB)->second))
                itBeginLB = m_map.emplace_hint(itBeginLB, keyBegin, val);
        } else { //replace current value
            (*itBeginLB).second = val;
        }

        //erase middle node between begin and end
        m_map.erase(++itBeginLB, itEndLB);
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.
