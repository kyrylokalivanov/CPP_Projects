#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "mylist.h"
#include <stdexcept>

namespace adt {

template<typename T>
class myqueue : private mylist<T> {
public:
    void enqueue(const T& value) {
        this->push_back(value);
    }

    T dequeue() {
        if (this->empty()) throw std::out_of_range("Queue is empty");
        T value = this->front();
        this->pop_front();
        return value;
    }

    bool empty() const {
        return mylist<T>::empty();
    }

    friend std::ostream& operator<<(std::ostream& os, const myqueue& queue) {
        os << static_cast<const mylist<T>&>(queue);
        return os;
    }
};

} // namespace adt

#endif

