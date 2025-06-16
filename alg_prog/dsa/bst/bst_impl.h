#ifndef BST_IMPL_H
#define BST_IMPL_H

#include "bst.h"

template <typename T>
class BST;

template <typename T>
Node<T>::Node(T t) : value{t}, left{nullptr}, right{nullptr} {}

template <typename T>
Node<T>::Node(T t, Node *left, Node *right) : value{t}, left{left}, right{right} {}

template <typename T>
Node<T>::Node(const Node &node)
{
    this->value = node.value;
    this->left = node.left ? new Node(*node.left) : nullptr;
    this->right = node.right ? new Node(*node.right) : nullptr;
}

template <typename T>
Node<T> &Node<T>::operator=(const Node<T> &other)
{
    if (this == &other)
        return *this;

    if (this->left != nullptr)
    {
        delete this->left;
    }
    if (this->right != nullptr)
    {
        delete this->right;
    }

    this->value = other.value;
    this->left = other.left ? new Node<T>(*other.left) : nullptr;
    this->right = other.right ? new Node<T>(*other.right) : nullptr;
    return *this;
}

template <typename T>
void BST<T>::destroy(Node<T> *node)
{
    // destruction is post-order

    if (node == nullptr)
    {
        return;
    }

    if (node->left == nullptr && node->right == nullptr)
    {
        delete node;
        node = nullptr;
        return;
    }

    if (node->left)
    {
        this->destroy(node->left);
    }
    if (node->right)
    {
        this->destroy(node->right);
    }

    delete node;
    node = nullptr;
}

template <typename T>
BST<T>::BST() : root{nullptr} {}

template <typename T>
BST<T>::BST(Node<T> *root) : root{root} {}

template <typename T>
BST<T>::~BST()
{
    this->destroy(this->root);
}

template <typename T>
void BST<T>::add(T t)
{
    if (this->root == nullptr)
    {
        this->root = new Node<T>(t);
        return;
    }

    Node<T> *current = this->root;
    while (true)
    {
        if (t < current->value)
        {
            if (current->left == nullptr)
            {
                current->left = new Node<T>(t);
                return;
            }
            current = current->left;
        }
        else
        {
            if (current->right == nullptr)
            {
                current->right = new Node<T>(t);
                return;
            }
            current = current->right;
        }
    }
}

template <typename T>
bool BST<T>::remove(T t)
{
    if (this->root == nullptr)
    {
        return false;
    }

    Node<T> *current = this->root;
    Node<T> *parent = nullptr;

    while (current != nullptr)
    {
        if (t < current->value)
        {
            parent = current;
            current = current->left;
        }
        else if (t > current->value)
        {
            parent = current;
            current = current->right;
        }
        else
        {
            // Node found
            if (current->left == nullptr && current->right == nullptr) // Leaf node
            {
                if (parent == nullptr) // Root node
                {
                    delete this->root;
                    this->root = nullptr;
                }
                else if (parent->left == current)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
                delete current;
            }
            else if (current->left == nullptr || current->right == nullptr) // One child
            {
                Node<T> *child = (current->left != nullptr) ? current->left : current->right;

                if (parent == nullptr) // Root node
                {
                    delete this->root;
                    this->root = child;
                }
                else if (parent->left == current)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
                delete current;
            }
            else // Two children
            {
                // Find the in-order successor (smallest in the right subtree)
                Node<T> *successorParent = current;
                Node<T> *successor = current->right;

                while (successor->left != nullptr)
                {
                    successorParent = successor;
                    successor = successor->left;
                }

                // Replace value and remove successor
                current->value = successor->value;

                if (successorParent->left == successor)
                {
                    successorParent->left = successor->right; // Remove successor
                }
                else
                {
                    successorParent->right = successor->right; // Remove successor
                }

                delete successor;
            }
            return true; // Value removed successfully
        }
    }

    return false;
}

template <typename T>
bool BST<T>::exists(T t) const
{
    Node<T> *current = this->root;

    while (current != nullptr)
    {
        if (t < current->value)
        {
            current = current->left;
        }
        else if (t > current->value)
        {
            current = current->right;
        }
        else
        {
            return true; // Value found
        }
    }

    return false; // Value not found
}

template <typename T>
std::vector<T> BST<T>::pre_order() const
{
    std::vector<T> traversal;
    this->pre_order_helper(this->root, traversal);
    return traversal;
}

template <typename T>
void BST<T>::pre_order_helper(Node<T> *node, std::vector<T> &traversal) const
{
    if (node == nullptr)
    {
        return;
    }

    traversal.push_back(node->value);
    this->pre_order_helper(node->left, traversal);
    this->pre_order_helper(node->right, traversal);
}

template <typename T>
std::vector<T> BST<T>::post_order() const
{
    std::vector<T> traversal;
    this->post_order_helper(this->root, traversal);
    return traversal;
}

template <typename T>
void BST<T>::post_order_helper(Node<T> *node, std::vector<T> &traversal) const
{
    if (node == nullptr)
    {
        return;
    }

    this->post_order_helper(node->left, traversal);
    this->post_order_helper(node->right, traversal);
    traversal.push_back(node->value);
}

template <typename T>
std::vector<T> BST<T>::in_order() const
{
    std::vector<T> traversal;
    this->in_order_helper(this->root, traversal);
    return traversal;
}

template <typename T>
void BST<T>::in_order_helper(Node<T> *node, std::vector<T> &traversal) const
{
    if (node == nullptr)
    {
        return;
    }

    this->in_order_helper(node->left, traversal);
    traversal.push_back(node->value);
    this->in_order_helper(node->right, traversal);
}

#endif // BST_IMPL_H