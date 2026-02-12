#include <iostream>
#include <cassert> 
#include "RedBlackTree.hpp"

int main() {
    RedBlackTree tree;
    
    std::cout << "Test Inserimento..." << std::endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    // Verify the search of the new values
    assert(tree.search(10) == true); 
    assert(tree.search(99) == false); // 99 doesn't exists

    std::cout << "base test passed!" << std::endl;
    
    return 0;
}