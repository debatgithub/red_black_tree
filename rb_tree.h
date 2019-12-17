#ifndef __INCLUDE_RB_TREE_H__
#define __INCLUDE_RB_TREE_H__
#include <iostream>
#include "rb_tree_node.h"
#include "binary_tree.h"
typedef enum e_rb_tree_error { RBT_CANT_FIND_NODE = -2, RBT_CANT_DELETE_NODE = -1,  RBT_SUCCESS = 0 } RBT_ERROR; 
template<class T>
class rb_tree : public binary_tree<T> {

public:
    rb_tree() : binary_tree<T>() { create_sentinel(); root = nil_node; }; 
    //rb_tree(rb_tree_node<T> *x) : binary_tree<T>(rb_tree_node<T> *x)  { create_sentinel(); root = nil_node; };
    rb_tree_node<T> *get_root(void ) {
        return root;
    }

   
    rb_tree_node<T> * search_rbt_node(rb_tree_node<T> *x, RBT_ERROR * p_rbt_error) {
        std::cout << "search rbt_node" << std::endl;
        if ((x == NULL) || (x == nil_node))  {
            *p_rbt_error = RBT_CANT_FIND_NODE;
            return x;
        }
        rb_tree_node<T> * y = root;
        while (y != nil_node) {
            TN_RESULT_TYPE res = y->compare_nodes((tree_node<T> *)x );
            if (res == TN_EQUAL_TO) {
                *p_rbt_error = RBT_SUCCESS;
                return y;
            }
            if (res == TN_GREATER_THAN) {
                if (y->get_right()!=nil_node)
                    y = (rb_tree_node<T> *)y->get_right();
                else {
                    *p_rbt_error = RBT_CANT_FIND_NODE;
                    return nil_node;
                }
            }
            else if (res == TN_LESS_THAN) {
                 if (y->get_left()!=nil_node)
                     y = (rb_tree_node<T> *)y->get_left();
                 else {
                     *p_rbt_error = RBT_CANT_FIND_NODE;
                     return nil_node;
                 }
            }
        }
        *p_rbt_error = RBT_CANT_FIND_NODE;
        return nil_node;
    };


    void insert_rbt_node(rb_tree_node<T> *z) {
        rb_tree_node<T> *x = root;
        rb_tree_node<T> *y = nil_node;
        T data = z->get_data();
        std::cout << "insert_rbt_node, node = " << z << ", data = " << data << ", root = " << x << ", nil_node = " << nil_node << std::endl;
        while (x != nil_node) {
            y = x;
            TN_RESULT_TYPE res = x->compare_nodes((tree_node<T> *)z );
            if (res == TN_LESS_THAN) 
                 x = (rb_tree_node<T> *)x->get_left();
            else if (res == TN_GREATER_THAN)
                 x = (rb_tree_node<T> *)x->get_right();
        }
        z->set_predecessor(y);
        if (y == nil_node) 
            root = z;
        else {
            TN_RESULT_TYPE res = y->compare_nodes(z );
            if (res == TN_LESS_THAN) 
                y->set_left(z);
            else 
                y->set_right(z);
        }
        z->set_left(nil_node);
        z->set_right(nil_node);
        z->set_color(RED_COLOR);
        rb_tree_insert_fixup(z);
    };

    void rb_tree_insert_fixup(rb_tree_node<T> *z) {
        std::cout << "rb_tree_insert_fixup, z = " << z << std::endl;
        while ((z != root) && (z->get_color() != BLACK_COLOR) && (((rb_tree_node<T> *)(z->get_predecessor())) != nil_node) && ((((rb_tree_node<T> *)(z->get_predecessor()))->get_color()) == RED_COLOR)) {
            if ((z->get_predecessor()) == (((z->get_predecessor())->get_predecessor())->get_left())) { 
                rb_tree_node<T> *y = (rb_tree_node<T> *)(((z->get_predecessor())->get_predecessor())->get_right());
                if (y->get_color() == RED_COLOR) {
                    ((rb_tree_node<T> *)(z->get_predecessor()))->set_color(BLACK_COLOR);
                    y->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)(z->get_predecessor()->get_predecessor()))->set_color(RED_COLOR);
                    z = (rb_tree_node<T> *)((z->get_predecessor())->get_predecessor());
                }
                else {
                    if (z == (rb_tree_node<T> *)(z->get_predecessor()->get_right())) {
                        z = (rb_tree_node<T> *)z->get_predecessor();
                        left_rotate(z);
                    }
                    ((rb_tree_node<T> *)(z->get_predecessor()))->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)((z->get_predecessor())->get_predecessor()))->set_color(RED_COLOR);
                    right_rotate((rb_tree_node<T> *)(z->get_predecessor()->get_predecessor()));
                }
            }
            else {
                rb_tree_node<T> *y = (rb_tree_node<T> *)(((z->get_predecessor())->get_predecessor())->get_left());
                if (y->get_color() == RED_COLOR) {
                    ((rb_tree_node<T> *)(z->get_predecessor()))->set_color(BLACK_COLOR);
                    y->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)(z->get_predecessor()->get_predecessor()))->set_color(RED_COLOR);
                    z = (rb_tree_node<T> *)((z->get_predecessor())->get_predecessor());
                }
                else {
                    if (z == (rb_tree_node<T> *)(z->get_predecessor()->get_left())) {
                        z = (rb_tree_node<T> *)z->get_predecessor();
                        right_rotate(z);
                    }
                    ((rb_tree_node<T> *)(z->get_predecessor()))->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)((z->get_predecessor())->get_predecessor()))->set_color(RED_COLOR);
                    left_rotate((rb_tree_node<T> *)(z->get_predecessor()->get_predecessor()));
                }
            }
        }
        root->set_color(BLACK_COLOR);
    };
 


 

    rb_tree_node<T> * rb_tree_minimum(rb_tree_node<T> * x) {
        while (((rb_tree_node<T> *)x->get_left()) != nil_node)
            x = (rb_tree_node<T> *)x->get_left();
        return x;
    };
    rb_tree_node<T> * rb_tree_maximum(rb_tree_node<T> * x) {
        while (((rb_tree_node<T> *)x->get_right()) != nil_node)
            x = (rb_tree_node<T> *)x->get_right();
        return x;
    };    

    rb_tree_node<T> * rb_tree_successor(rb_tree_node<T> *x) {
         std::cout << "rb_tree_successor" << std::endl;
        tree_node<T> * y = nil_node;
        if ((x->get_right()) != nil_node) 
            return rb_tree_minimum(x->get_right());
        y = x->get_predecessor();
        while ((y != nil_node) && (x == y->get_right())) {
            x = y;
            y = y->get_predecessor();
        }
        return y;
    };
 
 
    void rb_tree_transplant(rb_tree_node<T> * u, rb_tree_node<T> *v ) {
         std::cout << "rb_tree_transplant" << std::endl;
        if (u->get_predecessor() == nil_node)
            root = v;
        else if ((u->get_predecessor())->get_left() == u)
            (u->get_predecessor())->set_left(v);
        else
            (u->get_predecessor())->set_right(v);
        v->set_predecessor(u->get_predecessor());
    };        


   
    RBT_ERROR delete_rbt_node(rb_tree_node<T> * x) {
         std::cout << "delete_rbt_node" << std::endl;
        RBT_ERROR rbt_e;
        rb_tree_node<T> * z = search_rbt_node(x, &rbt_e);
        if (rbt_e == RBT_CANT_FIND_NODE) 
            return RBT_CANT_DELETE_NODE;
        rb_tree_node<T> * y = z;
        RBTN_COLOR_TYPE y_original_color = y->get_color();
        if (z->get_left() == nil_node) {
            x = (rb_tree_node<T> *)z->get_right();
            rb_tree_transplant(z, (rb_tree_node<T> *)z->get_right());
        }
        else if (z->get_right() == nil_node) {
            x = (rb_tree_node<T> *)z->get_left();
            rb_tree_transplant(z, (rb_tree_node<T> *)z->get_left());
        }
        else {
             y = rb_tree_minimum((rb_tree_node<T> *)z->get_right());
             y_original_color = y->get_color();
             x = (rb_tree_node<T> *)y->get_right();
             if (y->get_predecessor() == z) {
                 x->set_predecessor(y);
             }
             else {
                 rb_tree_transplant(y, (rb_tree_node<T> *)y->get_right());
                 y->set_right(z->get_right());
                 (y->get_right())->set_predecessor(y);
             }
             rb_tree_transplant(z, y);
             y->set_left(z->get_left());
             (y->get_left())->set_predecessor(y);
             
        }
        if (y_original_color == BLACK_COLOR)
            rb_tree_delete_fixup(x);
        return RBT_SUCCESS;
    };


    void rb_tree_delete_fixup(rb_tree_node<T> *x) {
        std::cout << "rb_tree_delete_fixup" << std::endl;
        while ((x != root) && (x->get_color() == BLACK_COLOR)) {
            if (x == (x->get_predecessor())->get_left()) {
                rb_tree_node<T> * w = (rb_tree_node<T> *)(x->get_predecessor())->get_right();
                if (w->get_color() == RED_COLOR) {
                    w->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)(x->get_predecessor()))->set_color(RED_COLOR);
                    left_rotate((rb_tree_node<T> *)x->get_predecessor());
                    w = (rb_tree_node<T> *)(x->get_predecessor())->get_right();
                }
                if ((((rb_tree_node<T> *)(w->get_left()))->get_color() == BLACK_COLOR) && (((rb_tree_node<T> *)(w->get_right()))->get_color() == BLACK_COLOR)) {
                    w->set_color(RED_COLOR);
                    x = (rb_tree_node<T> *)x->get_predecessor();
                }
                else {
                    if (((rb_tree_node<T> *)(w->get_right()))->get_color() == BLACK_COLOR) {
                        ((rb_tree_node<T> *)(w->get_left()))->set_color(BLACK_COLOR);
                        w->set_color(RED_COLOR);
                        right_rotate(w);
                        w = (rb_tree_node<T> *)((x->get_predecessor())->get_right());
                    }
                    w->set_color(((rb_tree_node<T> *)x->get_predecessor())->get_color());
                    ((rb_tree_node <T> *)(x->get_predecessor()))->set_color(BLACK_COLOR);
                    ((rb_tree_node <T> *)(w->get_right()))->set_color(BLACK_COLOR);
                    left_rotate((rb_tree_node<T> *)x->get_predecessor());
                    x = root;
                }
            }
            else {

                rb_tree_node<T> * w = (rb_tree_node<T> *)((x->get_predecessor())->get_left());
                if (w->get_color() == RED_COLOR) {
                    w->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)(x->get_predecessor()))->set_color(RED_COLOR);
                    right_rotate((rb_tree_node<T> *)x->get_predecessor());
                    w = (rb_tree_node<T> *)((x->get_predecessor())->get_left());
                }
                if ((((rb_tree_node<T> *)(w->get_right()))->get_color() == BLACK_COLOR) && (((rb_tree_node<T>*)w->get_left()))->get_color() == BLACK_COLOR) {
                    w->set_color(RED_COLOR);
                    x = (rb_tree_node<T> *)x->get_predecessor();
                }
                else {
                    if (((rb_tree_node<T> *)((w->get_left())))->get_color() == BLACK_COLOR) {
                        ((rb_tree_node<T> *)((w->get_right())))->set_color(BLACK_COLOR);
                        w->set_color(RED_COLOR);
                        left_rotate(w);
                        w = (rb_tree_node<T> *)((x->get_predecessor())->get_left());
                    }
                    w->set_color(((rb_tree_node<T> *)(x->get_predecessor()))->get_color());
                    ((rb_tree_node<T> *)x->get_predecessor())->set_color(BLACK_COLOR);
                    ((rb_tree_node<T> *)w->get_left())->set_color(BLACK_COLOR);
                    right_rotate((rb_tree_node<T> *)x->get_predecessor());
                    x = root;
                }
            }
            x->set_color(BLACK_COLOR);
        }
    };
                    
    void left_rotate(rb_tree_node<T> *x) {
        std::cout << "rb_tree left_rotate" << std::endl;
        rb_tree_node<T> * y = (rb_tree_node<T> *)x->get_right();
        x->set_right(y->get_left());
        if (y->get_left() != nil_node) 
            (y->get_left())->set_predecessor(x);
        y->set_predecessor(x->get_predecessor());
        if (x->get_predecessor() == nil_node) 
            root = y;
        else if (x == (x->get_predecessor())->get_left())
            (x->get_predecessor())->set_left(y);
        else 
            (x->get_predecessor())->set_right(y);
        y->set_left(x);
        x->set_predecessor(y);
    };
    void right_rotate(rb_tree_node<T> *x) {
        std::cout << "rb_tree right_rotate" << std::endl;
        rb_tree_node<T> * y = (rb_tree_node<T> *)x->get_left();
        x->set_left(y->get_right());
        if (y->get_right() != nil_node) 
            (y->get_right())->set_predecessor(x);
        y->set_predecessor(x->get_predecessor());
        if (x->get_predecessor() == nil_node) 
            root = y;
        else if (x == (x->get_predecessor())->get_right())
            (x->get_predecessor())->set_right(y);
        else 
            (x->get_predecessor())->set_left(y);
        y->set_right(x);
        x->set_predecessor(y);
    };

    void print_rb_tree_in_order(rb_tree_node<T> *x ) {
        if ((x != NULL) && (x != nil_node)) {
            print_rb_tree_in_order((rb_tree_node<T> *)x->get_left());
            x->print_node ();
            if (x->get_color() == BLACK_COLOR) 
                std::cout << " black " << std::endl;
            else
                std::cout << " red " << std::endl;
            print_rb_tree_in_order((rb_tree_node<T> *)x->get_right());
        }

    };

    void print_rb_tree_pre_order(rb_tree_node<T> *x ) {
        if ((x != NULL) && (x != nil_node)) {
            x->print_node ();
            if (x->get_color() == BLACK_COLOR) 
                std::cout << " black " << std::endl;
            else
                std::cout << " red " << std::endl;
            print_rb_tree_pre_order((rb_tree_node<T> *)x->get_left());
            print_rb_tree_pre_order((rb_tree_node<T> *)x->get_right());
        }
    };

    void print_rb_tree_post_order(rb_tree_node<T> *x ) {
        if ((x != NULL) && (x != nil_node)) {
            print_rb_tree_in_order((rb_tree_node<T> *)x->get_left());
            print_rb_tree_in_order((rb_tree_node<T> *)x->get_right());
            x->print_node ();
              if (x->get_color() == BLACK_COLOR) 
                std::cout << " black " << std::endl;
            else
                std::cout << " red " << std::endl;
       }
    };

    void create_sentinel(void ) {
        nil_node = new rb_tree_node<T>();
        nil_node->set_color(BLACK_COLOR);
    };

protected:
    rb_tree_node<T> * root;
    rb_tree_node<T> * nil_node;
};

#endif // __INCLUDE_RB_TREE_H__

         
