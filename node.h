#ifndef __INCLUDE_NODE_H__
#define __INCLUDE_NODE_H__
#include <iostream>
template <class T>
class node
{

public:
    node (T _data) { data = _data;};
    node () { data = 0; }
    T get_data(void ) { return data; }
    void print_node (void ) { 
           std::cout << data;
           std::cout << " "; 
    };
private:
    T data;


};
#endif // __INCLUDE_NODE_H__
