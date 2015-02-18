//
//  main.cpp
//
//  Created by Christian Deckert on 02/02/15.
//

#include <iostream>
#include <iterator>


template <typename T> struct mylist_iterator;

template <typename T> struct mylist_node;



template <typename T>
class mylist {
public:
    typedef mylist_iterator<T> iterator;
public:
    mylist() : head(NULL), tail(NULL) {}
    ~mylist() { delete head; }
    bool empty() const { return head == NULL; }
    void push_back(const T& elem);
    iterator begin() { return mylist_iterator<T>(head); }
    iterator end() { return mylist_iterator<T>(NULL); }
private:
    mylist_node<T> *head, *tail;
};





template <typename T>
struct mylist_iterator : public std::iterator<std::forward_iterator_tag, T> {
    friend class mylist<T>;
public:
    T& operator*();
    const mylist_iterator<T>& operator++();
    bool operator!=(const mylist_iterator<T>& other) const;
private:
    mylist_node<T> *pointee;
    mylist_iterator(mylist_node<T> *pointee) : pointee(pointee) {}
};





int main()
{
    
    return 0;
}





