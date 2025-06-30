#ifndef TRAITS_H
#define TRAITS_H

#include <cstring>

namespace adt {

template<typename T>
struct lessthan {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

template<typename T>
struct greaterthan {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

template<typename T>
struct lessthan<T*> {
    bool operator()(const T* a, const T* b) const {
        return *a < *b;
    }
};

template<typename T>
struct greaterthan<T*> {
    bool operator()(const T* a, const T* b) const {
        return *a > *b;
    }
};

template<>
struct lessthan<const char*> {
    bool operator()(const char* a, const char* b) const {
        return std::strcmp(a, b) < 0;
    }
};

template<>
struct greaterthan<const char*> {
    bool operator()(const char* a, const char* b) const {
        return std::strcmp(a, b) > 0;
    }
};

} // namespace adt

#endif
