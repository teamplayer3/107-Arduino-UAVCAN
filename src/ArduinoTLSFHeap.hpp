/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2020 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-UAVCAN/graphs/contributors.
 */

#ifndef ARDUINO_TLSF_HEAP_HPP_
#define ARDUINO_TLSF_HEAP_HPP_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "Arduino.h"
#include <tlsf/tlsf.h>
#include <vector>

#define TLFS_ALIGNED (sizeof(void *) * 4U)

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

struct AllocInfo
{
    bool alloc;
    size_t size;
    void *ptr;
};

void *allocate_intern(size_t const amount);
void free_intern(void *const pointer);

class ArduinoTLSFHeap
{
public:
    const static tlsf_t TLSF;
    static std::vector<AllocInfo> alloc_statistics;

    ArduinoTLSFHeap() {}

    void *allocate(size_t const amount)
    {
        return allocate_intern(amount);
    }

    void free(void *const pointer)
    {
        free_intern(pointer);
    }
};

template <class T>
class StdLikeAllocator
{
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T value_type;

    StdLikeAllocator() {}
    StdLikeAllocator(const StdLikeAllocator &) {}

    pointer allocate(size_type n, const void * = 0)
    {
        T *t = (T *)allocate_intern(n * sizeof(T));
        return t;
    }

    void deallocate(void *p, size_type)
    {
        if (p)
        {
            free_intern(p);
        }
    }

    pointer address(reference x) const
    {
        return &x;
    }
    const_pointer address(const_reference x) const { return &x; }
    StdLikeAllocator<T> &operator=(const StdLikeAllocator &) { return *this; }
    void construct(pointer p, const T &val)
    {
        new ((T *)p) T(val);
    }
    void destroy(pointer p) { p->~T(); }

    size_type max_size() const { return size_t(-1); }

    template <class U>
    struct rebind
    {
        typedef StdLikeAllocator<U> other;
    };

    template <class U>
    StdLikeAllocator(const StdLikeAllocator<U> &) {}

    template <class U>
    StdLikeAllocator &operator=(const StdLikeAllocator<U> &) { return *this; }
};

#endif /* ARDUINO_O1_HEAP_HPP_ */