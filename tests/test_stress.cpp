#include "RedBlackTree.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    RedBlackTree tree;
    int N = 10000;
    
    for(int i = 0; i < N; i++) {
        tree.insert(rand() % 100000);
    }
    
    tree.verifyProperties();
    
    std::cout << N << " node inserted with no errors." << std::endl;
    return 0;
}