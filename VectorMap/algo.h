#ifndef ALGO_H
#define ALGO_H
#include <iterator>

namespace Estd {

template <class ForwardIter, class T, class Compare=std::less<>>
ForwardIter lower_bound(ForwardIter begin_, ForwardIter end_, const T& val, Compare compare = {})
{
    typename std::iterator_traits<ForwardIter>::difference_type range, half;
    range = std::distance(begin_, end_);

    ForwardIter it_middle;

    // range must always decreases
    // begin_ end is including not excluding
    while(range > 0)
    {
        half = range/2;
        it_middle   = begin_ + half;

        if(compare(*it_middle,val)) {
            begin_ = ++it_middle;
            range  -= half+1;
        } else {
            range = half;
        }
    }

    return begin_;
}

template <class ForwardIter, class T, class Compare=std::less<>>
ForwardIter binary_search(ForwardIter begin_, ForwardIter end_, const T& val, Compare compare = {})
{
    typename std::iterator_traits<ForwardIter>::difference_type range, half;
    range = std::distance(begin_, end_);

    ForwardIter it_middle;

    // range must always decreases
    // begin_ end is including not excluding
    while(range > 0)
    {
        half = range/2;
        it_middle   = begin_ + half;

        if(compare(*it_middle,val)) {
            begin_ = ++it_middle;
            range  -= half+1;
        } else {
            range = half;
        }
    }

    return ((begin_ == end_) || compare(val,*begin_)) ? end_ : begin_;
}

template <class ForwardIter, class T, class Comp = std::less<>>
std::pair<ForwardIter,ForwardIter> equal_range(ForwardIter begin_, ForwardIter end_, const T& val, Comp comp = {})
{
    using difference_t = typename std::iterator_traits<ForwardIter>::difference_type;
    difference_t half_range, range = std::distance(begin_, end_);
    ForwardIter middle_;

    while(range > 0) {
        half_range = range/2;
        middle_ = begin_ + half_range;

        if(comp(*middle_,val)) {
            begin_ = ++middle_;
            range -= half_range+1;
        } else {
            range = half_range;
        }
    }

    ForwardIter last_(begin_);
    while ((last_ != end_) && !comp(val, *last_))
        ++last_;

    return std::pair<ForwardIter,ForwardIter>(begin_, last_);
}

template <class ForwardIter, class T, class Comp = std::less<>>
ForwardIter upper_bound(ForwardIter begin_, ForwardIter end_, const T& val, Comp comp = {})
{
    using difference_t = typename std::iterator_traits<ForwardIter>::difference_type;
    difference_t half_range, range = std::distance(begin_, end_);
    ForwardIter middle_;

    while(range > 0)
    {
        half_range = range/2;
        middle_ = begin_ + half_range;

        if(!comp(val, *middle_)) {
            begin_ = ++middle_;
            range -= half_range+1;
        } else {
            range = half_range;
        }
    }
    return begin_;
}


}//Estd

#endif // ALGO_H

