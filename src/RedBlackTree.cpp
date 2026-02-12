#include "RedBlackTree.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>


#define RESET   "\033[0m"
#define RED_TXT "\033[31m"      // Red
#define BLK_TXT "\033[90m"      // Black

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

void RedBlackTree::Left_Rotate(Node* x) {
    
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

void RedBlackTree::Right_Rotate(Node* x) {
    
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

void RedBlackTree::remove_fixup(Node* &x) {
    Node* w = NIL;
    while( x != root and x->color == BLACK){
        if(x == x->parent->left){                                           // x is a left child?
            w = x->parent->right;                                           // w is x's sibling 
            if(w->color == RED){
                w->color = BLACK;                                           // |
                x->parent->color = RED;                                     // | CASE 1
                Left_Rotate(x->parent);                                     // | 
                w = x->parent->right;                                       // |
            }
            if(w->left->color == BLACK and w->right->color == BLACK){
                w->color = RED;                                             // | CASE 2
                x = x->parent;                                              // | 
            }else{
                if(w->right->color == BLACK){                               
                    w->left->color = BLACK;                                 // |
                    w->color = RED;                                         // | CASE 3
                    Right_Rotate(w);                                        // |
                    w = x->parent->right;                                   // |
                }
                w->color = x->parent->color;                                // |
                x->parent->color = BLACK;                                   // | CASE 4
                w->right->color = BLACK;                                    // |
                Left_Rotate(x->parent);                                     // |
                x = root;                                                   // |
            }
        }else{
            w = x->parent->left;                                            // w is x's sibling 
            if(w->color == RED){
                w->color = BLACK;                                           // |
                x->parent->color = RED;                                     // | CASE 1
                    Right_Rotate(x->parent);                                    // | 
                w = x->parent->left;                                        // |
            }
            if(w->right->color == BLACK and w->left->color == BLACK){
                w->color = RED;                                             // | CASE 2
                x = x->parent;                                              // | 
            }else{
                if(w->left->color == BLACK){                               
                    w->right->color = BLACK;                                // |
                    w->color = RED;                                         // | CASE 3
                    Left_Rotate(w);                                         // |
                    w = x->parent->left;                                    // |
                }
                w->color = x->parent->color;                                // |
                x->parent->color = BLACK;                                   // | CASE 4
                w->left->color = BLACK;                                     // |
                Right_Rotate(x->parent);                                    // |
                x = root;                                                   // |
            }

        }
    }
x->color = BLACK;
};

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
        root = z;
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
        if(key < z->data){
            z = z->left;
        }else{
            z = z->right;
        }
    }
    //assert(z != NIL and "Errore: Tentativo di rimuovere una chiave inesistente!"); 

    Node* y = z;
    Node* x = NIL;
    bool y_original_color = y->color;

    if (z->left == NIL){

        x = z->right;
        Transplant(z,z->right);         // Replace z by its right child

    }else if (z->right == NIL){

        x = z->left;
        Transplant(z,z->left);          // Replace z by its left child

    }else{

        y = Tree_minimum(z->right);
        y_original_color  = y->color;
        x = y->right;

        if( y!= z->right){              // is y father down the tree ? 

            Transplant(y,y->right);     // Replace y by its right child
            y->right = z->right;        // z's right child becomes
            y->right->parent = y;       // y's right child

        }else x->parent = y;            // In case y is NIL 
        
        Transplant(z,y);                // Replace z by its successor y
        y->left = z->left;              // and give z's left child to y,
        y->left->parent = y;            // which had no left child
        y->color = z->color;
    }
    if(y_original_color == BLACK)       // if any red-black violation occurred,
        remove_fixup(x);                // correct them
};

bool RedBlackTree::search(int key) {
    Node *z = root;

    while (z != NIL and key != z->data){
        if(key < z->data)
            z = z->left;
        else z = z->right;

    }

    if (z == NIL) return 0;
    else return 1;
};

void RedBlackTree::verifyProperties() {
    if (root == NIL) return;

    // 1. Root must be black
    assert(root->color == BLACK);

    // 2. Recursive check for consecutive Reds and black height
    checkNodes(root);
};

int RedBlackTree::checkNodes(Node* n) {
    if (n == NIL) return 1; // Leafs are BLACK
    
    // Rule: a RED node can't have RED child
    if (n->color == RED) {
        assert(n->left->color == BLACK);
        assert(n->right->color == BLACK);
    }

    // Rule: Every path from root to leaf must have the same black height
    int leftBlackHeight = checkNodes(n->left);
    int rightBlackHeight = checkNodes(n->right);

    // If the black heights are different the tree is not balanced!
    assert(leftBlackHeight == rightBlackHeight && "Violation of the black height!");

    // Return the current Black height
    return (n->color == BLACK) ? leftBlackHeight + 1 : leftBlackHeight;
};

void RedBlackTree::printTree(Node* root, int space) {
    if (root == NULL) return;

    // Aumenta la distanza tra i livelli
    space += 10;

    // Elabora prima il figlio destro (apparirà in alto)
    printTree(root->right, space);

    // Stampa il nodo corrente dopo lo spazio
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    
    // Mostra il colore (R per Red, B per Black)
    char color = (root->color == RED) ? 'R' : 'B';
    printf("[%d%c]\n", root->data, color);

    // Elabora il figlio sinistro (apparirà in basso)
    printTree(root->left, space);
}

void RedBlackTree::printHelper(Node* x, std::string indent, bool last) {
    if (x != NIL) {
        std::cout << indent;
        if (last) {
            std::cout << "└────";
            indent += "     ";
        } else {
            std::cout << "├────";
            indent += "|    ";
        }

        // chose the color from the node property
        std::string sColor = (x->color == RED) ? RED_TXT : BLK_TXT;
        std::cout << sColor << x->data << " (" << (x->color == RED ? "R" : "B") << ")" << RESET << std::endl;

        printHelper(x->left, indent, false);
        printHelper(x->right, indent, true);
    }
}

void RedBlackTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
}

void RedBlackTree::deleteTreeHelper(Node* node) {

    if (node != NIL && node != nullptr) {
        deleteTreeHelper(node->left);   
        deleteTreeHelper(node->right);  
        delete node;                    
    }
}

RedBlackTree::~RedBlackTree() {
    deleteTreeHelper(this->root); 
    delete NIL;                 
}