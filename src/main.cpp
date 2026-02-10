/*#include <iostream>
#include <cstdio>
#include "RedBlackTree.hpp"

int main() {
    printf("Hello Red-Black Tree! \n");
    
    RedBlackTree RBT;

    //RBT.printTree(RBT.getroot(),5);
    for( int i=0; i< 10; i++){
      printf("i = %i \n",i);
      RBT.insert(i);
      RBT.verifyProperties(); 
      if( i%4 == 0){
        printf("remove %i \n", i);
        RBT.remove(i); 
      }
    }
    RBT.printTree(RBT.getroot(),1);
  return 0;
}*/
#include <iostream>
#include <cstdio>
#include "RedBlackTree.hpp"
int main() {
    RedBlackTree tree;
    
    // Let's insert some values
    int values[] = {10, 20,50, 30, 90, 60, 15, 80, 40 ,100};
    
    for(int v : values) {
        tree.insert(v);
    }
    //Let's verify the properies for a RBT
    tree.verifyProperties();
    
    std::cout << "The tree is balanced and all the Properties hold:" << std::endl;
    tree.prettyPrint();

    return 0;
}