#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include <vector>
#include <functional>

//using Container = std::vector<int>;
//using Compare   = std::less<int>;
//using value_t   = int;
//using size_type = unsigned int;
//using iterator_t= std::vector<int>::iterator;

template <typename Container, typename Compare, typename iterator_t = typename Container::iterator,
          typename value_t = typename Container::value_type, typename size_type = typename Container::size_type>
iterator_t binary_search_impl(Container& c, const value_t& val, iterator_t begin_, size_t N)
{
    if(N == 1)
        return (!(val < *begin_) && !(*begin_ < val))? begin_ : c.end();

    iterator_t half = begin_ + N/2;
    if(!(val<*half))
        return binary_search_impl(c, val, begin_+N/2, N-N/2);
    else
        return binary_search_impl(c,val, begin_, N/2);
}

template <typename Container, typename Compare, typename iterator_t = typename Container::iterator,
          typename value_t = typename Container::value_type, typename size_type = typename Container::size_type>
iterator_t binary_search(Container& c, const value_t& val)
{
    return binary_search_impl(c, val, c.begin(), c.size());
}

#endif // BINARY_SEARCH_H

