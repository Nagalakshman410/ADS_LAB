#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *parent, *left, *right;
};

class RedBlackTree {
private:
    Node *root;

    // Helper function to rotate left
    void rotateLeft(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Helper function to rotate right
    void rotateRight(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Helper function to fix the violation after BST insert
    void fixViolation(Node *&ptr) {
        Node *parentPtr = nullptr;
        Node *grandParentPtr = nullptr;
        while ((ptr != root) && (ptr->color != BLACK) && (ptr->parent->color == RED)) {
            parentPtr = ptr->parent;
            grandParentPtr = ptr->parent->parent;

            /*  Case : A
                Parent of ptr is left child of Grand-parent of ptr */
            if (parentPtr == grandParentPtr->left) {
                Node *unclePtr = grandParentPtr->right;

                /* Case : 1
                   The uncle of ptr is also red
                   Only Recoloring required */
                if (unclePtr != nullptr && unclePtr->color == RED) {
                    grandParentPtr->color = RED;
                    parentPtr->color = BLACK;
                    unclePtr->color = BLACK;
                    ptr = grandParentPtr;
                } else {
                    /* Case : 2
                       ptr is right child of its parent
                       Left-rotation required */
                    if (ptr == parentPtr->right) {
                        rotateLeft(parentPtr);
                        ptr = parentPtr;
                        parentPtr = ptr->parent;
                    }

                    /* Case : 3
                       ptr is left child of its parent
                       Right-rotation required */
                    rotateRight(grandParentPtr);
                    std::swap(parentPtr->color, grandParentPtr->color);
                    ptr = parentPtr;
                }
            } else {
                /* Case : B
                   Parent of ptr is right child of Grand-parent of ptr */
                Node *unclePtr = grandParentPtr->left;

                /*  Case : 1
                    The uncle of ptr is also red
                    Only Recoloring required */
                if ((unclePtr != nullptr) && (unclePtr->color == RED)) {
                    grandParentPtr->color = RED;
                    parentPtr->color = BLACK;
                    unclePtr->color = BLACK;
                    ptr = grandParentPtr;
                } else {
                    /* Case : 2
                       ptr is left child of its parent
                       Right-rotation required */
                    if (ptr == parentPtr->left) {
                        rotateRight(parentPtr);
                        ptr = parentPtr;
                        parentPtr = ptr->parent;
                    }

                    /* Case : 3
                       ptr is right child of its parent
                       Left-rotation required */
                    rotateLeft(grandParentPtr);
                    std::swap(parentPtr->color, grandParentPtr->color);
                    ptr = parentPtr;
                }
            }
        }
        root->color = BLACK;
    }

    // Helper function to insert a new node with given data
    void insertBST(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->color = RED;

        Node *parent = nullptr;
        Node *current = root;

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

        fixViolation(newNode);
    }

    // Helper function to print the tree (inorder traversal)
    void inorder(Node *ptr) {
        if (ptr == nullptr)
            return;
        inorder(ptr->left);
        std::cout << ptr->data << "(" << (ptr->color == RED ? "RED" : "BLACK") << ") ";
        inorder(ptr->right);
    }

public:
    RedBlackTree() : root(nullptr) {}

    // Public method to insert data into the tree
    void insert(int data) {
        insertBST(data);
        std::cout << "After inserting " << data << ": ";
        inorder(root);
        std::cout << std::endl;
    }
};

int main() {
    RedBlackTree tree;
    char choice;

    do {
        int value;
        std::cout << "Enter value to insert: ";
        std::cin >> value;

        tree.insert(value);

        std::cout << "Do you want to insert another value? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
