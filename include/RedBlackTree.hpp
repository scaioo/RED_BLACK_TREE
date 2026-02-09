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
        
        // Root and Sentinel 
        Node *root;
        Node *NIL;

        // Rotation
        void Left_Rotate(Node*& A);
        void Right_Rotate(Node*& A);

        // Fixup
        void insert_fixup(Node*& A);
        void remove_fixup(Node*& A);
    
    public:

        // Constructor
        RedBlackTree() : root(nullptr) {};

        // Define primitive function: insert search delete
        void insert(int key);
        void remove(int key);
        bool search(int key);


};  

#endif 