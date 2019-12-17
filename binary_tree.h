#ifndef __INCLUDE_BINARY_TREE_H__
#define __INCLUDE_BINARY_TREE_H__
#include <iostream>
#include "tree_node.h"
typedef enum e_binary_tree_error { BT_CANT_FIND_NODE = -2, BT_CANT_DELETE_NODE = -1,  BT_SUCCESS = 0 } BT_ERROR; 

template<class T>
class binary_tree {

public:
    binary_tree() { root = NULL; }; 
    binary_tree(tree_node<T> *x)  {
         root = x;
    };
    ~binary_tree() { };
    tree_node<T> *get_root(void ) {
        return root;
    }

    tree_node<T> * search_node(tree_node<T> *x, BT_ERROR * p_bt_error) {
        if (x == NULL) {
            *p_bt_error = BT_CANT_FIND_NODE;
            return x;
        }
        tree_node<T> * y = root;
        while (y != NULL) {
            TN_RESULT_TYPE res = y->compare_nodes(x );
            if (res == TN_EQUAL_TO) {
                *p_bt_error = BT_SUCCESS;
                return y;
            }
            if (res == TN_GREATER_THAN) {
                if (y->get_right()!=NULL)
                    y = y->get_right();
                else {
                    *p_bt_error = BT_CANT_FIND_NODE;
                    return NULL;
                }
            }
            else if (res == TN_LESS_THAN) {
                 if (y->get_left()!=NULL)
                     y = y->get_left();
                 else {
                     *p_bt_error = BT_CANT_FIND_NODE;
                     return NULL;
                 }
            }
        }
        *p_bt_error = BT_CANT_FIND_NODE;
        return NULL;
    };


    void insert_node(tree_node<T> *z) {
        tree_node<T> *x = root;
        tree_node<T> *y = NULL;
        while (x != NULL) {
            y = x;
            TN_RESULT_TYPE res = x->compare_nodes(z );
            if (res == TN_LESS_THAN) 
                x = x->get_left();
            else if (res == TN_GREATER_THAN)
                x = x->get_right();
        }
        z->set_predecessor(y);
        if (y == NULL) {
            root = z;
        }
        else {
            TN_RESULT_TYPE res = y->compare_nodes(z );
            if (res == TN_LESS_THAN) 
                y->set_left(z);
            else 
                y->set_right(z);
        }
    };
    tree_node<T> * tree_minimum(tree_node<T> * x) {
        while (x->get_left() != NULL)
            x = x->get_left();
        return x;
    };
    tree_node<T> * tree_maximum(tree_node<T> * x) {
        while (x->get_right() != NULL)
            x = x->get_right();
        return x;
    };    

    tree_node<T> * tree_successor(tree_node<T> *x) {
        tree_node<T> * y = NULL;
        if ((x->get_right()) != NULL) 
            return tree_minimum(x->get_right());
        y = x->get_predecessor();
        while ((y != NULL) && (x == y->get_right())) {
            x = y;
            y = y->get_predecessor();
        }
        return y;
    };
 
 
    void transplant(tree_node<T> * u, tree_node<T> *v ) {
        if (u->get_predecessor() == NULL)
            root = v;
        else if ((u->get_predecessor())->get_left() == u)
            (u->get_predecessor())->set_left(v);
        else
            (u->get_predecessor())->set_right(v);
        if (v != NULL)
            v->set_predecessor(u->get_predecessor());
    };        


   
    BT_ERROR delete_node(tree_node<T> * x) {
        BT_ERROR bt_e;
        tree_node<T> * z = search_node(x, &bt_e);
        if (bt_e == BT_CANT_FIND_NODE) 
            return BT_CANT_DELETE_NODE;
        if (z->get_left() == NULL)
            transplant(z, z->get_right());
        else if (z->get_right() == NULL)
            transplant(z, z->get_left());
        else {
             tree_node<T> * y = tree_minimum(z->get_right());
             if (y->get_predecessor() != z) {
                 transplant(y, y->get_right());
                 y->set_right(z->get_right());
                 (y->get_right())->set_predecessor(y);
             }
             transplant(z, y);
             y->set_left(z->get_left());
             (y->get_left())->set_predecessor(y);
        }
        return BT_SUCCESS;
    };


    void print_tree_in_order(tree_node<T> *x ) {
        if (x != NULL) {
            print_tree_in_order(x->get_left());
            x->print_node ();
            print_tree_in_order(x->get_right());
        }

    };

    void print_tree_pre_order(tree_node<T> *x ) {
        if (x != NULL) {
            x->print_node ();
            print_tree_pre_order(x->get_left());
            print_tree_pre_order(x->get_right());
        }
    };

    void print_tree_post_order(tree_node<T> *x ) {
        if (x != NULL) {
            print_tree_in_order(x->get_left());
            print_tree_in_order(x->get_right());
            x->print_node ();
        }
    };
protected:
    tree_node<T> * root;
};

#endif // __INCLUDE_BINARY_TREE_H__

         
