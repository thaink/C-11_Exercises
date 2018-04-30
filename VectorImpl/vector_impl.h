/*
 * For implementation of vector only
 * author: thank@capp.snu.ac.kr
 */

#ifndef ESTD_VECTOR_IMPL_H
#define ESTD_VECTOR_IMPL_H

#include <memory>

namespace Estd {
    template <class T, class A = std::allocator<T>>
    struct vector_base{
        using value_type = T;
        A alloc;          //allocator
        value_type* elem; //start of allocation
        value_type* space;//end of element sequence, start of space allocated for posible expansion
        value_type* last; //end of allocated space

        vector_base(const A& a, typename A::size_type n)
            :alloc{a}, elem{alloc.allocate(n)}, space{elem}, last{elem+n} {}
        ~vector_base(){alloc.deallocate(elem, last-elem);}

        vector_base(const vector_base&) = delete;
        vector_base& operator=(const vector_base&) = delete;
        vector_base(vector_base&&);
        vector_base& operator=(vector_base&&);
    };

}//Estd

#endif // ESTD_VECTOR_IMPL_H

