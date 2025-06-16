// Binary Search Trees (BSTs) are ADTs used to store data in a sorted manner
// Binary Trees (BTs) are a type of a tree data structure where each node has at most two children.
//
//                  1
//                 / |
//                2   7
//              /  |
//             3    4
// BSTs are sorting this data in a specific manner:
// *    the children left to the node are all < than the node;
// *    the children right to the node are > than the node;
// This allows for additions and searches in O(logn) time, as only a branch of the tree is queried
// It can result in O(n) time if the tree is unbalanced, for instance:
//
//                    1
//                   /
//                  0
//                 /
//               ...
//               /
//           -100
//             /
//         -101
// The structure of the tree is not guarranteed if an arbitrary order of operations is chosen: the structure can be changed
// greatly. Example:
//                      10
//                     /  |
//                    5    15
//                         /
//                       12
// Now we add 13 -> it becomes the right sibling of 12
//                     10
//                    /  |
//                   5   15
//                       / |
//                     12   13
// If we remove it, the structure remains the same as the initial one:
//                      10
//                     /  |
//                    5    15
//                         /
//                       12
// But if we remove initially 15 from the tree, it becomes
//                      10
//                     /  |
//                    5    12
// If we add 15 back again, the tree becomes:
//                      10
//                     /  |
//                    5    12
//                           |
//                            15

// There are many techniques in which a tree can be traversed:
//  *   pre-order:   root -> left -> right
//  *   post-order:  left -> right -> root
//  *   in-order:    left -> root -> right

#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <vector>

template <typename T>
class BST;

template <typename T>
class Node
{
    friend class BST<T>;

private:
    T value;
    Node *left;
    Node *right;

public:
    Node(T t);
    Node(T t, Node *left, Node *right);

    Node(const Node &node);

    Node &operator=(const Node &other);

    ~Node() = default;
};

template <typename T>
class BST
{
private:
    Node<T> *root;

    void destroy(Node<T> *node);
    void pre_order_helper(Node<T> *node, std::vector<T>& traversal) const;
    void post_order_helper(Node<T> *node, std::vector<T>& traversal) const;
    void in_order_helper(Node<T> *node, std::vector<T>& traversal) const;

public:
    BST();
    BST(Node<T> *root);

    void add(T t);

    bool remove(T t);

    bool exists(T t) const;

    std::vector<T> pre_order() const;
    std::vector<T> post_order() const;
    std::vector<T> in_order() const;

    ~BST();
};

#include "bst_impl.h"

#endif // BST_H