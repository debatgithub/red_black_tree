#include <iostream>
#include "rb_tree_node.h"
#include "rb_tree.h"
int main (void );
#define TREE_MAX 4
int tree_vals[TREE_MAX] = { 25, 35, 50, 80 };
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

    p_node = new rb_tree_node<int>(121);
    q_node = p_rbt->search_rbt_node(p_node, &rbt_e);
    if (rbt_e == RBT_SUCCESS) 
         std::cout << "Red Black tree search_node() passed" << std::endl; 
    else
         std::cout << "Red Black  tree search_node() failed" << std::endl;

    p_node = new rb_tree_node<int>(123);
    rbt_e = p_rbt->delete_rbt_node(p_node);
    if (rbt_e == RBT_SUCCESS) 
         std::cout << "Red Black tree delete_node() passed" << std::endl; 
    else
         std::cout << "Red Black tree delete_node() failed" << std::endl;
 
    std::cout << "Tree now" << std::endl;
    p_rbt->print_rb_tree_pre_order(p_rbt->get_root());
    std::cout << std::endl;

  
    delete p_rbt;
    return 0;

   
}


        
