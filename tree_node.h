#ifndef __INCLUDE_TREE_NODE_H__
#define __INCLUDE_TREE_NODE_H__
#include <iostream>
#include "node.h" 
typedef enum e_tn_result_type { TN_GREATER_THAN = -2, TN_LESS_THAN = -1, TN_EQUAL_TO = 0 } TN_RESULT_TYPE;
template <class T>
class tree_node : public node<T>
{
    
public:
    tree_node<T>() : node<T>() { pred = left = right = NULL; };
    tree_node<T>(T n) : node<T>(n) { pred = left = right = NULL; };
    tree_node<T> * get_left(void ) { return left; };
    void set_left(tree_node<T> * _left) { left = _left; }
    tree_node<T> * get_right(void ) { return right; };
    void set_right(tree_node<T> * _right) { right = _right; }
    tree_node<T> * get_predecessor(void ) { return pred; };
    void set_predecessor(tree_node<T> * _pred) { pred = _pred; }
    TN_RESULT_TYPE compare_nodes(tree_node<T> * x) { 
        if (x->get_data() > this->get_data())
            return TN_GREATER_THAN;
        else if (x->get_data() < this->get_data())
            return TN_LESS_THAN;
        else
            return TN_EQUAL_TO;
   };
protected:
    tree_node * left;
    tree_node * right;
    tree_node * pred;
 

};
#endif // __INCLUDE_TREE_NODE_H__
