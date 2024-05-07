#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <vector>
#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data);
};

class RedBlackTree {
private:
    Node *root;

    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertRBTree(Node *&);
    void fixDeleteRBTree(Node *&);
    void inorderHelper(Node *&, std::vector<int> res);
    Node* successor(Node *&);
    Node* minValueNode(Node *&);
    void deleteNodeHelper(Node *&, int);
    void fixDoubleBlack(Node *&);
    void transplant(Node *&root, Node *u, Node *v);
    
public:
    RedBlackTree();
    void insert(const int &);
    void remove(const int &);
    void inorder(std::vector<int> res);
    Node* search(const int &);
};

#endif
