#ifndef MYSTACK_H
#define MYSTACK_H

#include "mylist.h"
#include <stdexcept>

namespace adt {

template<typename T>
class mystack : private mylist<T> {
public:
    void push(const T& value) {
        this->push_front(value);
    }

    T pop() {
        if (this->empty()) throw std::out_of_range("Stack is empty");
        T value = this->front();
        this->pop_front();
        return value;
    }

    bool empty() const {
        return mylist<T>::empty();
    }

    friend std::ostream& operator<<(std::ostream& os, const mystack& stack) {
        os << static_cast<const mylist<T>&>(stack);
        return os;
    }
};

} // namespace adt

#endif
