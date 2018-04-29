a basic vector implementation will include:
- a handle holding pointer to the first element
- one-past-the-last element
- one-past-the-last allocated space
- an allocator from which the vector can acquire memory for its elements
	- it could be alloc or the default allocator which is new and delete

strong and optimized assignment code:
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


