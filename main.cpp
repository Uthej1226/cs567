#include <iostream>
#include "redblacktree.h"

int main() {
    RedBlackTree tree;

    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);

    std::vector<int> inorderRes;

    std::cout << "Inorder Traversal of Red-Black Tree: ";
    tree.inorder(inorderRes);
    std::cout << std::endl;

    tree.remove(18);
    std::cout << "Inorder Traversal after deletion of 18: ";
    tree.inorder(inorderRes);
    std::cout << std::endl;

    return 0;
}
