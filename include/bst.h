// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        
        Node(const T& val) : key(val), count(1), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    void insert(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node(value);
            return;
        }
        
        if (value < node->key) {
            insert(node->left, value);
        } else if (value > node->key) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }
    
    int depth(Node* node) const {
        if (node == nullptr) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }
    
    bool search(Node* node, const T& value) const {
        if (node == nullptr) return false;
        if (value == node->key) return true;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }
    
    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back({node->key, node->count});
        collectNodes(node->right, nodes);
    }
    
public:
    BST() : root(nullptr) {}
    
    ~BST() {
        clear(root);
    }
    
    void insert(const T& value) {
        insert(root, value);
    }
    
    int depth() const {
        return depth(root);
    }
    
    bool search(const T& value) const {
        return search(root, value);
    }
    
    void inorderTraversal(void (*visit)(const T&, int)) const {
        inorderTraversal(root, visit);
    }
    
    void inorderTraversal(Node* node, void (*visit)(const T&, int)) const {
        if (node == nullptr) return;
        inorderTraversal(node->left, visit);
        visit(node->key, node->count);
        inorderTraversal(node->right, visit);
    }
    
    std::vector<std::pair<T, int>> getNodesSortedByCount() const {
        std::vector<std::pair<T, int>> nodes;
        collectNodes(root, nodes);
        std::sort(nodes.begin(), nodes.end(), 
                  [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                      return a.second > b.second;
                  });
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
