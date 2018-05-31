#ifndef __BITPOOL_H__
#define __BITPOOL_H__

// This BitPool will allocate a contiguous array of objects of type [T]. It
// internally keeps track of object state as 'in use' and 'free' using a separate
// allocation block of bits; one bit per object in the pool.
// An object is marked as 'in use' when GetObject() is called and it is
// considered to be in use by the calling system. An object is 'free' 
// when it either has not yet been retrieved by GetObject() or when it has 
// been returned to the pool by ReturnObject().

#include <iostream>

template <typename T>
class BitPool 
{
public:
    // Allocates a contiguous array of type [type]. Allocates some additional
    // things to keep track of BitPool state.
    // @poolSize - The number of elements to allocate for the BitPool
    BitPool(size_t poolSize);

    // Deallocates all items which were allocated in the initial constructor.
    ~BitPool();

    // @returns A new object, internally marked as 'in use', or nullptr if
    // error (i.e. There are no other objects that can be used in this pool)
    T * GetObject();

    // Given a pointer to the [pType] object, returns it to the pool
    // for use at another time, internally marks the object as 'free'.
    // @pType The object to return to the pool
    // @returns Whether or not the return was successful. 
    bool ReturnObject(T *pType);

    // Returns an object at the given index, whether the object is 'in use' or
    // 'free'. An index out of range returns nullptr
    // @index The zero-indexed object to return from the pool
    // @returns An object at the given index, nullptr if the object is out of
    // bounds
    T * GetObjectAt(size_t index);

    // @returns The number of objects currently marked 'in use' in this BitPool
    size_t GetObjectsInUse() const;

    // @returns The pool size of this BitPool, the maximum potential
    // objects that can be called from GetObject().
    size_t GetMaxObjects() const;

private:
    T *pTypeArray_;       //! The pointer to the contiguous array of [T]
    size_t poolSize;      //! The size of the pool
};

template <typename T>
BitPool<T>::BitPool(size_t poolSize) 
{
    pTypeArray_ = (T)std::malloc(poolSize * sizeof(T));
    this.poolSize = poolSize;
}

template <typename T>
BitPool<T>::~BitPool() 
{
    std::free(pTypeArray_);
}

template <typename T>
T * BitPool<T>::GetObject()
{
    //TODO
    return nullptr;
}

template <typename T>
bool BitPool<T>::ReturnObject(T *pType)
{
    //TODO
    return false;
}

template <typename T>
T * BitPool<T>::GetObjectAt(size_t index)
{
    if (index >= poolSize) return nullptr;
    return pTypeArray_[index];
}

template <typename T>
size_t BitPool<T>::GetObjectsInUse() const
{
    //TODO
    return 0;
}

template <typename T>
size_t BitPool<T>::GetMaxObjects() const
{
    return poolSize;
}

#endif //__BITPOOL_H__
