#include <iostream>
#include <cstdio>
#include "RedBlackTree.hpp"
int main() {
    RedBlackTree tree;
    
    // Let's insert some values
    int values[] = {10, 20,50, 30, 90, 60, 15, 80, 40 ,100, 30,44, 78, 36};
    
    for(int v : values) {
        tree.insert(v);
    }
    // Let's verify the properies for a RBT
    tree.verifyProperties();
    std::cout << "The tree is balanced and all the Properties hold:" << std::endl;
    
    // Let's print the output
    tree.prettyPrint();

    return 0;
}