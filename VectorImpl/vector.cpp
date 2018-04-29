/*
 * Vector Implementation
 * author: thaink@capp.snu.ac.kr
 */

#include <memory>
#include "vector.h"

using namespace Estd;
using std::allocator;

/*
 * implementation of vector_base
 */

template<class T, class A>
vector_base<T,A>::vector_base(vector_base<T,A>&& a)
    :alloc(a.alloc),
      elem(a.elem),
      space(a.space),
      last(a.last)
{
    a.elem = a.space = a.last = nullptr;
}

template<class T, class A>
vector_base<T,A>& vector_base<T,A>::operator=(vector_base<T,A>&& a)
{
    swap(*this, a);
    return *this;
}


/*
 * implementation of vector
 */
template <class T, class A>
Estd::vector<T,A>::vector(size_type n, const value_type& val, const A& talloc)
    :vb(talloc,n)
{
    std::uninitialized_fill(vb.elem, vb.elem+n, val);
}

template <class T, class A>
void vector<T,A>::destroy_elements()
{
    for (T* p = vb.elem; p!=vb.space; ++p)
        p->~T();
    vb.space = vb.elem;
}

template <class T, class A>
vector<T,A>::~vector()
{
    destroy_elements();
}

template <class T, class A>
vector<T,A>::vector(const vector<T,A>& a)
    :vb{a.vb.alloc, a.size()}
{
    std::uninitialized_copy(a.begin(), a.end(), vb.elem);
}

template <class T, class A>
vector<T,A>& vector<T,A>::operator=(const vector<T,A>& a)
{
    if (capability() < a.size()) { //allocate new vector representation
        vector temp{a};
        swap(*this, temp);
        return *this;
    }

    if (this == &a) return *this;

    size_type sz=size();
    size_type asz=a.size();
    vb.alloc = a.vb.alloc;
    if(asz<=sz) {
        copy(a.begin(), a.end(), vb.elem);
        for (T* p=vb.elem+asz; p<vb.space;++p)
            p->~T();
    } else {
        copy(a.begin(), a.end(), vb.elem);
        std::uninitialized_copy(a.begin()+sz, a.end(), vb.space);
    }
    vb.space = vb.elem + asz;
    return *this;
}

template <class T, class A>
vector<T,A>::vector(vector<T,A>&& a)
    :vb{std::move(a.vb)}
{
}

template <class T, class A>
vector<T,A>& vector<T,A>::operator=(vector<T,A>&& a)
{
    this->clear(); //redundance. assme rvalue being destroyed immediately
    std::swap(*this, a); //swap work because we define move assignment for sub-class
}


template<typename It1, typename It2>
static void uninitialized_move(It1 I, It1 E, It2 Dest) {
    std::uninitialized_copy(std::make_move_iterator(I),
                            std::make_move_iterator(E), Dest);
}

template <class T, class A>
void vector<T,A>::reserve(size_type newalloc)
{
    if(newalloc <= capability()) return;
    vector_base<T,A> b(vb.alloc, newalloc);
    uninitialized_move(vb.elem, vb.space, b.elem);
    b.space = b.elem + size();
    swap(vb,b);
}// implicitly release old value


template <class T, class A>
void vector<T,A>::push_back(const value_type& val)
{
    if(capability()==size())
        reserve(size()?2*size():8);
    vb.alloc.construct(vb.space, val);
    ++vb.space;
}










