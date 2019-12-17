#include <iostream>
#include "rb_tree_node.h"
#include "rb_tree.h"
int main (void );
//#define TREE_MAX 20
//int tree_vals[TREE_MAX] = { 3, 7, 10, 12, 14, 15, 16, 17, 19, 20, 21, 23, 26, 28, 30, 35, 38, 39, 41, 47 };
#define TREE_MAX 5
int tree_vals[TREE_MAX] = { 3, 7, 10, 12, 14 };
int main (void ) 
{

    rb_tree<int> * p_rbt = new rb_tree<int>();
    rb_tree_node<int> *p_node;
    rb_tree_node<int> *q_node;
    RBT_ERROR rbt_e;

    if (p_rbt == NULL) {
        std::cout << "Red Black tree constructor failed" << std::endl;
        return 1;
    }
    std::cout << "Red Black tree constructor passed" << std::endl;
 
    for (int i = 0; i < TREE_MAX; i++) {
        p_node = new rb_tree_node<int>(tree_vals[i]);
        std::cout << "Node address = " << p_node << std::endl;
        if (p_node != NULL)
            p_rbt->insert_rbt_node(p_node);
        else
            std::cout << "Red Black Tree node creation failed" << std::endl;
        std::cout << "Red Black Tree root = " << p_rbt->get_root() << std::endl;
    }
    std::cout << "Red Black tree  insert_node() passed" << std::endl;
    std::cout << "Tree now -" << std::endl;
    p_rbt->print_rb_tree_pre_order(p_rbt->get_root());
    std::cout << std::endl;


  
    delete p_rbt;
    return 0;

   
}


        
