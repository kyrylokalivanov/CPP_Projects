About

This project implements a template-based singly linked list (mylist<T>) with a nested mynode<T> class, a queue (myqueue<T>), and a stack (mystack<T>) in the adt namespace. It also includes utility functions for sorting (sort) and checking sortedness (issorted). The code adheres to the assignment requirements, including dynamic memory management, exception handling, and support for copy/move semantics.

Features

mylist<T> (Singly Linked List)

Defined in the adt namespace with a private nested mynode<T> class.
Supports:
    Insertion at the beginning, end, or specific position.
    Deletion from the beginning, end, or specific position.
    Deletion of the first or all occurrences of a value.
    Finding the position of the first occurrence of a value.
    Counting occurrences of a value.
    Checking if the list is empty.

Copy/move constructors and assignment operators.
Initialization with std::initializer_list<T>.
Stream output operator (operator<<) for readable printing.
Proper memory cleanup with destructor.

myqueue<T> and mystack<T>

Non-public inheritance from mylist<T>.
Throw std::out_of_range for operations on empty queue/stack.
Queue: Enqueue/dequeue operations.
Stack: Push/pop operations.

Utility Functions

adt::issorted<T, Compare>: Checks if the list is sorted (default: lessthan<T>).
adt::sort<T, Compare>: Sorts the list (default: lessthan<T>).
Comparison traits:
    lessthan<T>: Uses operator<.
    greaterthan<T>: Uses operator>.
    Specializations for pointers, including const char*.



