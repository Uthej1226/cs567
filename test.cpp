#include <deepstate/DeepState.hpp>
#include "redblacktree.h"

using namespace deepstate;

TEST(RedBlackTree, Insertion) {
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

    ASSERT(tree.search(7) != nullptr);
    ASSERT(tree.search(3) != nullptr);
    ASSERT(tree.search(18) != nullptr);
    ASSERT(tree.search(10) != nullptr);
    ASSERT(tree.search(22) != nullptr);
    ASSERT(tree.search(8) != nullptr);
    ASSERT(tree.search(11) != nullptr);
    ASSERT(tree.search(26) != nullptr);
    ASSERT(tree.search(2) != nullptr);
    ASSERT(tree.search(6) != nullptr);
    ASSERT(tree.search(13) != nullptr);
}

TEST(RedBlackTree, Deletion) {
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

    tree.remove(18);

    ASSERT(tree.search(18) == nullptr);
}

TEST(RedBlackTree, InorderTraversal) {
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

    std::vector<int> expected_inorder = {2, 3, 6, 7, 8, 10, 11, 13, 18, 22, 26};
    std::vector<int> actual_inorder;

    tree.inorder(actual_inorder);

    for(int i=0; i<actual_inorder.length(); i++)
        ASSERT(actual_inorder[i] == expected_inorder[i]);
}

TEST(RedBlackTree, Search) {
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

    ASSERT(tree.search(7) != nullptr);
    ASSERT(tree.search(3) != nullptr);
    ASSERT(tree.search(18) != nullptr);
    ASSERT(tree.search(10) != nullptr);
    ASSERT(tree.search(22) != nullptr);
    ASSERT(tree.search(8) != nullptr);
    ASSERT(tree.search(11) != nullptr);
    ASSERT(tree.search(26) != nullptr);
    ASSERT(tree.search(2) != nullptr);
    ASSERT(tree.search(6) != nullptr);
    ASSERT(tree.search(13) != nullptr);
}

TEST(RedBlackTree, EmptyTreeSearch) {
    RedBlackTree tree;

    ASSERT(tree.search(7) == nullptr);
}

TEST(RedBlackTree, EmptyTreeDeletion) {
    RedBlackTree tree;

    tree.remove(7); // Should not cause any issues with an empty tree
}

int main(int argc, char **argv) {
    DeepState_InitOptions(argc, argv);
    DeepState_Run();
    return 0;
}
