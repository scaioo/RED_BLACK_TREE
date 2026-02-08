#ifndef RedBlackTree_h
#define RedBlackTree_h
class RedBlackTree {
    private:
        // Define the color type
        enum Color {RED, BLACK};

        // Define the structure of a node in the red-black tree
        struct Node {
            int data;
            Color color;
            Node *right, *left, *parent;

            Node (int val) : data(val), color(RED) , left(nullptr), right(nullptr), parent(nullptr) {};    
        };

};

#endif