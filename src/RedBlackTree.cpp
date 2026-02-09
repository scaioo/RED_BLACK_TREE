#include "RedBlackTree.hpp"
#include <cassert>

void RedBlackTree::Transplant(Node* &u, Node* &v){
    
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
    
};

RedBlackTree::Node* RedBlackTree::Tree_minimum(Node* x){
    while (x->left != NIL) {
        x = x->left;
    }
    return x;
};

void RedBlackTree::Left_Rotate(Node*& x) {
    
    Node* y = x->right;
    x->right = y->left;
    if(y->left != NIL) 
        y->left->parent = x;

    y->parent = x->parent;
    if(x->parent == NIL) 
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;

    y->left = x;
    x->parent = y;
};

void RedBlackTree::Right_Rotate(Node*& x) {
    
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
};

void RedBlackTree::insert_fixup(Node* &z) {
    
    Node* y = NIL;

    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){   // is z's parent a left child ? 
            y = z->parent->parent->right;           // y is z'uncle
            if(y->color == RED){                    // are z's parent and uncle both red?
                z->parent->color = BLACK;           //  |
                y->color = BLACK;                   //  CASE 1
                z->parent->parent->color = RED;     //  |
                z = z->parent->parent;              //  |
            }else{
                if( z == z->parent->right){         //  |
                    z = z->parent;                  //  CASE 2
                    Left_Rotate(z);                 //  |
                }
                z->parent->color = BLACK;           //  |
                z->parent->parent->color = RED;     //  CASE 3
                Right_Rotate(z->parent->parent);    //  |
            }
        }else{                                      // z's parent a right child 
            y = z->parent->parent->left;            // y is z'uncle
            if(y->color == RED){                    // are z's parent and uncle both red?
                z->parent->color = BLACK;           //  |
                y->color = BLACK;                   //  CASE 1
                z->parent->parent->color = RED;     //  |
                z = z->parent->parent;              //  |
            }else{
                if( z == z->parent->left){          //  |
                    z = z->parent;                  //  CASE 2
                    Right_Rotate(z);                //  |
                }
                z->parent->color = BLACK;           //  |
                z->parent->parent->color = RED;     //  CASE 3
                Left_Rotate(z->parent->parent);     //  |
            }            
        }
    }
    root->color = BLACK;
};

void RedBlackTree::remove_fixup(Node*& x) {};

void RedBlackTree::insert(int key) {
    
    Node* z = new Node(key);
    Node* x = root;
    Node* y = NIL;

    while(x != NIL){
        y = x;
        if (z->data < x->data)
            x=x->left;
        else x = x->right;
    }
    
    z->parent = y;
    
    if(y == NIL) 
        root = NIL;
    else if (z->data < y->data)
        y->left = z;
    else y->right = z;
    
    z->left = NIL;
    z->right = NIL;
    z-> color = RED;
    
    insert_fixup(z);
};

void RedBlackTree::remove(int key) {
    Node* z = root;
    // find the node with the key value
    while (z != NIL and key != z->data){
        if(key < z->data)
            z = z->left;
        else z = z->right;
    }
    assert(z != NIL and "Errore: Tentativo di rimuovere una chiave inesistente!"); 

    Node* y = z;
    Node* x = NIL;
    bool y_original_color = y->color;

    if (z->left == NIL){
        x = z->right;

    }

};

bool RedBlackTree::search(int key) {return 0;};