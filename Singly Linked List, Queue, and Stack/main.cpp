#include "mylist.h"
#include "myqueue.h"
#include "mystack.h"
#include "traits.h"
#include <iostream>
#include <string>

using namespace adt;

void test_list() {
    std::cout << "Testing mylist<int>...\n";
    mylist<int>* list = new mylist<int>{1, 2, 3};
    std::cout << "Initial list: " << *list << "\n";

    list->push_front(0);
    std::cout << "After push_front(0): " << *list << "\n";

    list->push_back(4);
    std::cout << "After push_back(4): " << *list << "\n";

    list->insert(2, 10);
    std::cout << "After insert(2, 10): " << *list << "\n";

    list->pop_front();
    std::cout << "After pop_front(): " << *list << "\n";

    list->pop_back();
    std::cout << "After pop_back(): " << *list << "\n";

    list->erase(1);
    std::cout << "After erase(1): " << *list << "\n";

    list->remove(2);
    std::cout << "After remove(2): " << *list << "\n";

    list->push_back(3);
    list->push_back(3);
    std::cout << "After adding two 3s: " << *list << "\n";

    list->remove_all(3);
    std::cout << "After remove_all(3): " << *list << "\n";

    std::cout << "Find 10: " << list->find(10) << "\n";
    std::cout << "Count 10: " << list->count(10) << "\n";
    std::cout << "Is empty: " << (list->empty() ? "true" : "false") << "\n";

    delete list;
}

void test_queue() {
    std::cout << "\nTesting myqueue<std::string>...\n";
    myqueue<std::string>* queue = new myqueue<std::string>;
    queue->enqueue("apple");
    queue->enqueue("banana");
    std::cout << "Queue: " << *queue << "\n";
    std::cout << "Dequeue: " << queue->dequeue() << "\n";
    std::cout << "Queue after dequeue: " << *queue << "\n";
    try {
        while (!queue->empty()) queue->dequeue();
        queue->dequeue(); // Should throw
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
    delete queue;
}

void test_stack() {
    std::cout << "\nTesting mystack<double>...\n";
    mystack<double>* stack = new mystack<double>;
    stack->push(1.5);
    stack->push(2.5);
    std::cout << "Stack: " << *stack << "\n";
    std::cout << "Pop: " << stack->pop() << "\n";
    std::cout << "Stack after pop: " << *stack << "\n";
    try {
        while (!stack->empty()) stack->pop();
        stack->pop(); // Should throw
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
    delete stack;
}

void test_sorting() {
    std::cout << "\nTesting sorting with mylist<int>...\n";
    mylist<int>* list = new mylist<int>{3, 1, 4, 1, 5};
    std::cout << "Unsorted list: " << *list << "\n";
    std::cout << "Is sorted (lessthan): " << (issorted<int, lessthan<int>>(*list) ? "true" : "false") << "\n";
    sort<int, lessthan<int>>(*list);
    std::cout << "Sorted list (lessthan): " << *list << "\n";
    std::cout << "Is sorted (lessthan): " << (issorted<int, lessthan<int>>(*list) ? "true" : "false") << "\n";

    sort<int, greaterthan<int>>(*list);
    std::cout << "Sorted list (greaterthan): " << *list << "\n";
    std::cout << "Is sorted (greaterthan): " << (issorted<int, greaterthan<int>>(*list) ? "true" : "false") << "\n";
    delete list;

    std::cout << "\nTesting sorting with mylist<const char*>...\n";
    mylist<const char*>* str_list = new mylist<const char*>{"banana", "apple", "cherry"};
    std::cout << "Unsorted list: " << *str_list << "\n";
    sort<const char*, lessthan<const char*>>(*str_list);
    std::cout << "Sorted list (lessthan): " << *str_list << "\n";
    sort<const char*, greaterthan<const char*>>(*str_list);
    std::cout << "Sorted list (greaterthan): " << *str_list << "\n";
    delete str_list;
}

int main() {
    test_list();
    test_queue();
    test_stack();
    test_sorting();
    return 0;
}
