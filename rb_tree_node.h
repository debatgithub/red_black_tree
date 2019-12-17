#ifndef __INCLUDE_RB_TREE_NODE_H__
#define __INCLUDE_RB_TREE_NODE_H__
#include <iostream>
#include "tree_node.h" 
typedef enum e_rbtn_color_type { RED_COLOR = 0, BLACK_COLOR = 1 } RBTN_COLOR_TYPE;
template <class T>
class rb_tree_node : public tree_node<T>
{
    
public:
    rb_tree_node<T>() : tree_node<T>() { color = RED_COLOR; };
    rb_tree_node<T>(T n) : tree_node<T>(n) { color = RED_COLOR; };
    RBTN_COLOR_TYPE get_color(void ) { return color; };
    void set_color(RBTN_COLOR_TYPE _color ) { color = _color; }
    void toggle_color(void ) { color = (color == RED_COLOR) ? BLACK_COLOR : RED_COLOR; };
protected:
    RBTN_COLOR_TYPE color;
 

};
#endif // __INCLUDE_RB_TREE_NODE_H__
