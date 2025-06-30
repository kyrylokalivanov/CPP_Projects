#ifndef MYLIST_H
#define MYLIST_H

#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include "traits.h"

namespace adt {

template<typename T>
class mylist {
private:
    struct mynode {
        T data;
        mynode* next;
        mynode(const T& value) : data(value), next(nullptr) {}
    };

    mynode* head;
    size_t size;

    void copy(const mylist& other) {
        head = nullptr;
        size = 0;
        mynode* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            mynode* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

public:
    // Iterator-like class for traversing the list
    class iterator {
        mynode* ptr;
    public:
        iterator(mynode* p) : ptr(p) {}
        T& operator*() { return ptr->data; }
        iterator& operator++() { ptr = ptr->next; return *this; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        mynode* get_ptr() const { return ptr; }
    };

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }

    mylist() : head(nullptr), size(0) {}

    mylist(std::initializer_list<T> init) : head(nullptr), size(0) {
        for (const T& item : init) {
            push_back(item);
        }
    }

    mylist(const mylist& other) : head(nullptr), size(0) {
        copy(other);
    }

    mylist(mylist&& other) noexcept : head(other.head), size(other.size) {
        other.head = nullptr;
        other.size = 0;
    }

    ~mylist() {
        clear();
    }

    mylist& operator=(const mylist& other) {
        if (this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }

    mylist& operator=(mylist&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void push_front(const T& value) {
        mynode* new_node = new mynode(value);
        new_node->next = head;
        head = new_node;
        ++size;
    }

    void push_back(const T& value) {
        mynode* new_node = new mynode(value);
        if (!head) {
            head = new_node;
        } else {
            mynode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        ++size;
    }

    void insert(size_t pos, const T& value) {
        if (pos > size) {
            throw std::out_of_range("Position out of range");
        }
        if (pos == 0) {
            push_front(value);
            return;
        }
        mynode* new_node = new mynode(value);
        mynode* current = head;
        for (size_t i = 0; i < pos - 1; ++i) {
            if (!current) throw std::out_of_range("Position out of range");
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        ++size;
    }

    void pop_front() {
        if (!head) throw std::out_of_range("List is empty");
        mynode* temp = head;
        head = head->next;
        delete temp;
        --size;
    }

    void pop_back() {
        if (!head) throw std::out_of_range("List is empty");
        if (!head->next) {
            delete head;
            head = nullptr;
            --size;
            return;
        }
        mynode* current = head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        --size;
    }

    void erase(size_t pos) {
        if (!head) throw std::out_of_range("List is empty");
        if (pos >= size) throw std::out_of_range("Position out of range");
        if (pos == 0) {
            pop_front();
            return;
        }
        mynode* current = head;
        for (size_t i = 0; i < pos - 1; ++i) {
            if (!current) throw std::out_of_range("Position out of range");
            current = current->next;
        }
        mynode* temp = current->next;
        current->next = temp->next;
        delete temp;
        --size;
    }

    void remove(const T& value) {
        if (!head) return;
        if (head->data == value) {
            pop_front();
            return;
        }
        mynode* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        if (current->next) {
            mynode* temp = current->next;
            current->next = temp->next;
            delete temp;
            --size;
        }
    }

    void remove_all(const T& value) {
        while (head && head->data == value) {
            pop_front();
        }
        mynode* current = head;
        while (current && current->next) {
            if (current->next->data == value) {
                mynode* temp = current->next;
                current->next = temp->next;
                delete temp;
                --size;
            } else {
                current = current->next;
            }
        }
    }

    size_t find(const T& value) const {
        mynode* current = head;
        size_t pos = 0;
        while (current) {
            if (current->data == value) return pos;
            current = current->next;
            ++pos;
        }
        return size;
    }

    size_t count(const T& value) const {
        size_t count = 0;
        mynode* current = head;
        while (current) {
            if (current->data == value) ++count;
            current = current->next;
        }
        return count;
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t get_size() const {
        return size;
    }

    T& front() const {
        if (!head) throw std::out_of_range("List is empty");
        return head->data;
    }

    friend std::ostream& operator<<(std::ostream& os, const mylist& list) {
        mynode* current = list.head;
        os << "[ ";
        while (current) {
            os << current->data;
            if (current->next) os << ", ";
            current = current->next;
        }
        os << " ]";
        return os;
    }
};

template<typename T, typename Compare = lessthan<T>>
bool issorted(const mylist<T>& list) {
    if (list.empty() || list.get_size() == 1) return true;
    auto it = list.begin();
    auto next = it;
    ++next;
    while (next != list.end()) {
        if (!Compare()(*it, *next)) return false;
        ++it;
        ++next;
    }
    return true;
}

template<typename T, typename Compare = lessthan<T>>
void sort(mylist<T>& list) {
    if (list.empty() || list.get_size() == 1) return;

    mylist<T> sorted;
    while (!list.empty()) {
        T min = list.front();
        auto min_it = list.begin();
        size_t min_pos = 0, pos = 0;
        for (auto it = list.begin(); it != list.end(); ++it, ++pos) {
            if (Compare()(*it, min)) {
                min = *it;
                min_it = it;
                min_pos = pos;
            }
        }
        sorted.push_back(min);
        list.erase(min_pos);
    }
    list = std::move(sorted);
}

} // namespace adt

#endif
