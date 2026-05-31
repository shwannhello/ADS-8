// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <utility>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& val) : key(val), count(1), left(nullptr), right(nullptr) {}
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
        return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
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
        nodes.push_back(std::make_pair(node->key, node->count));
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

    std::vector<std::pair<T, int>> getNodesSortedByCount() const {
        std::vector<std::pair<T, int>> nodes;
        collectNodes(root, nodes);
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = i + 1; j < nodes.size(); ++j) {
                if (nodes[i].second < nodes[j].second) {
                    std::swap(nodes[i], nodes[j]);
                }
            }
        }
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
