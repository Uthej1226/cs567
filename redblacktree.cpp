#include "redblacktree.h"
#include <iostream>

Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

void RedBlackTree::rotateLeft(Node *&root) {
    Node *child = root->right;
    root->right = child->left;
    if (root->right)
        root->right->parent = root;
    child->parent = root->parent;
    if (!root->parent)
        this->root = child;
    else if (root == root->parent->left)
        root->parent->left = child;
    else
        root->parent->right = child;
    child->left = root;
    root->parent = child;
}

void RedBlackTree::rotateRight(Node *&root) {
    Node *child = root->left;
    root->left = child->right;
    if (root->left)
        root->left->parent = root;
    child->parent = root->parent;
    if (!root->parent)
        this->root = child;
    else if (root == root->parent->left)
        root->parent->left = child;
    else
        root->parent->right = child;
    child->right = root;
    root->parent = child;
}

void RedBlackTree::fixInsertRBTree(Node *&root) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (root != this->root && root->color != BLACK && root->parent->color == RED) {
        parent = root->parent;
        grandparent = root->parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                root = grandparent;
            } else {
                if (root == parent->right) {
                    rotateLeft(parent);
                    root = parent;
                    parent = root->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                root = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                root = grandparent;
            } else {
                if (root == parent->left) {
                    rotateRight(parent);
                    root = parent;
                    parent = root->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                root = parent;
            }
        }
    }
    this->root->color = BLACK;
}

void RedBlackTree::insert(const int &data) {
    Node *newNode = new Node(data);
    if (!root) {
        root = newNode;
        root->color = BLACK;
        return;
    }
    Node *current = root;
    Node *parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    fixInsertRBTree(newNode);
}

void RedBlackTree::fixDoubleBlack(Node *&root) {
    if (root == this->root)
        return;
    Node *sibling = nullptr;
    Node *parent = nullptr;
    while (root != this->root && root->color == BLACK) {
        parent = root->parent;
        if (root == parent->left) {
            sibling = parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rotateLeft(parent);
                sibling = parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                root = parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(parent);
                root = this->root;
            }
        } else {
            sibling = parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rotateRight(parent);
                sibling = parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                root = parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(parent);
                root = this->root;
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::remove(const int &data) {
    if (!root)
        return;
    Node *v = search(data), *u;
    if (!v)
        return;
    deleteNodeHelper(root, data);
}

void RedBlackTree::deleteNodeHelper(Node *&root, int key) {
    // Find the node to delete
    Node *z = root;
    while (z != nullptr && z->data != key) {
        if (key < z->data)
            z = z->left;
        else
            z = z->right;
    }

    if (z == nullptr) {
        std::cout << "Node with key " << key << " not found in the tree." << std::endl;
        return;
    }

    Node *x, *y = z;
    Color originalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (originalColor == BLACK)
        fixDoubleBlack(x);
}

void RedBlackTree::transplant(Node *&root, Node *u, Node *v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}


Node* RedBlackTree::minValueNode(Node *&node) {
    Node *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* RedBlackTree::successor(Node *&node) {
    Node *temp = node;
    while (temp->left != nullptr)
        temp = temp->left;
    return temp;
}

void RedBlackTree::inorderHelper(Node *&node, std::vector<int> res) {
    if (node == nullptr)
        return;
    inorderHelper(node->left, res);
    std::cout << node->data << " ";
    res.push_back(node->data, res);
    inorderHelper(node->right);
}

void RedBlackTree::inorder(std::vector<int> res) {
    inorderHelper(root, res);
}

Node* RedBlackTree::search(const int &data) {
    Node *current = root;
    while (current != nullptr) {
        if (current->data == data)
            return current;
        else if (current->data < data)
            current = current->right;
        else
            current = current->left;
    }
    return nullptr;
}