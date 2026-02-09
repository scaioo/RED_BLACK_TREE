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

        // Support Functions
        void Transplant(Node* &x, Node* &y);
        Node* Tree_minimum(Node* x);

        // Rotation
        void Left_Rotate(Node* &x);
        void Right_Rotate(Node* &x);

        // Fixup
        void insert_fixup(Node* &x);
        void remove_fixup(Node* &x);
    
    public:

        // Constructor
        RedBlackTree() {
            // create a single sentinel node and mark it BLACK
            NIL = new Node(0);
            NIL->color = BLACK;
            NIL->left = NIL->right = NIL->parent = nullptr;
            root = NIL;
        };

        // Define primitive function: insert search delete
        void insert(int key);
        void remove(int key);
        bool search(int key);


};  

#endif 