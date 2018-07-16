#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <class T>
class MIterator {
private:
    T it_begin, it_end;
public:
    MIterator(T begin, T end): it_begin(begin), it_end(end){}
    T next() {return it_begin++;}
    bool hasNext(){return it_begin != it_end;}
};

template <class T, class I>
class IF {
private:
    std::list<T> iterlist;
    typename std::list<T>::iterator current_it;

    void circular_it() {
        current_it++;
        if(current_it == iterlist.end()) current_it = iterlist.begin();
    }
public:
  IF(std::list<T> l): iterlist{l}, current_it{iterlist.begin()}{
  }

  I next(){
    I res = current_it->next();
    circular_it();
    while(!current_it->hasNext()) {
        if(iterlist.size()==1) break; // current_it should be keep valid
        typename std::list<T>::iterator old_it(current_it);
        circular_it();
        iterlist.erase(old_it);
    }
    return res;
  }

  bool hasNext(){
    if(iterlist.size()==0) return 0;
    return current_it->hasNext();
  }
};

int main()
{
    using iterator_t = typename std::vector<int>::iterator;
    using iterlist_t = typename std::list<MIterator<iterator_t>>;

    vector<int> vec1{1,2,3};
    vector<int> vec2{4,5};
    vector<int> vec3{6,7,8,9};
    iterlist_t iterlist{{vec1.begin(),vec1.end()}, {vec2.begin(),vec2.end()}, {vec3.begin(),vec3.end()}};
    IF<MIterator<iterator_t>, iterator_t> if1(iterlist);
    while(if1.hasNext())
        cout << *(if1.next()) << " ";
    cout << endl;
    cout << "Hello World!" << endl;
    return 0;
}

