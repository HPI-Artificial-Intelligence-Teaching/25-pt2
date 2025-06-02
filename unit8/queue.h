/******************************************************************************
 *
 *  A generic queue using a singly linked list.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iterator>
#include <stdexcept>

using namespace std;

// Implements a queue with a linked list
template <typename T>
class Queue {
    // stores the queue elements as a linked list
    struct List {
        T data;
        List* next;
    } *head, *last;

    // copys an existing list
    List* deep_copy_list(List* new_head, List* new_last) {
        // set the last pointer
        if (new_head == new_last)
            last = head;

        // copy the list by first deep-copying the tail and then linking it
        if (new_head) {
            auto tail = deep_copy_list(new_head->next, new_last);
            List* head = new List();
            head->data = new_head->data;
            head->next = tail;
            return (head);
        }

        return (nullptr);
    }

    // frees the list and sets the head to NULL
    void free_list() {
        while (head) {
            List* tmp = head->next;
            delete head;
            head = tmp;
        }
        last = nullptr;
        return;
    }

   public:
    // constructor
    Queue() : head(nullptr), last(nullptr) {}

    // copy constructor
    Queue(const Queue& q) { head = deep_copy_list(q.head, q.last); }

    // move constructor
    Queue(Queue&& q) : head(q.head), last(q.last) {
        q.head = nullptr;
        q.last = nullptr;
    }

    // copy assignment
    Queue& operator=(const Queue& q) {
        // free the existing queue
        free_list();
        // copy the queue passed in
        head = deep_copy_list(q.head, q.last);
        return (*this);
    }

    // move assignment
    Queue& operator=(Queue&& q) {
        // free the existing stack
        free_list();

        head = q.head;
        last = q.last;
        q.head = nullptr;
        q.last = nullptr;
        return (*this);
    }

    // destructor
    ~Queue() {
        free_list();
    }

    // is_empty method
    bool is_empty() const {
        return (head == nullptr);
    }

    // enqueue method
    void enqueue(const T& x) {
        List* old_last = last;
        last = new List();
        last->data = x;
        last->next = nullptr;
        if (is_empty())
            head = last;
        else
            old_last->next = last;
    }

    // dequeue method
    T dequeue() {
        if (is_empty())
            throw logic_error("Calling dequeue on an empty queue");

        List* tmp = head->next;
        T ret_value = head->data;
        delete head;
        head = tmp;
        if (is_empty())
            last = nullptr;

        return (ret_value);
    }

    // front method
    const T& front() const {
        if (is_empty())
            throw logic_error("Calling front on an empty queue");

        return (head->data);
    }

    // adding an iterator over the items of the queue
    struct Iterator {
        using iterator_category = forward_iterator_tag;
        using difference_time = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        reference operator*() const { return m_ptr->data; };
        pointer operator->() { return &m_ptr->data; };
        Iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        };
        Iterator operator++(int) {
            Iterator tmp = *this;
            m_ptr = m_ptr->next;
            return tmp;
        };

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        Iterator(List* ptr) : m_ptr(ptr) {}

       private:
        List* m_ptr;
    };
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

#endif