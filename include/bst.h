// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* addNode(Node* root, const T& data) {
    if (!root) {
      return new Node(data);
    } else if (data < root->key) {
      root->left = addNode(root->left, data);
    } else if (data > root->key) {
      root->right = addNode(root->right, data);
    } else {
      root->count++;
    }
    return root;
  }

  int searchNode(Node* root, const T& data) const {
    if (!root) return 0;
    if (data == root->key) return root->count;
    if (data < root->key) return searchNode(root->left, data);
    return searchNode(root->right, data);
  }

  int depthNode(Node* root) const {
    if (!root) return 0;
    int leftDepth = depthNode(root->left);
    int rightDepth = depthNode(root->right);
    return (leftDepth > rightDepth ?
      leftDepth : rightDepth) + 1;
  }

  void inorder(Node* root, std::vector<std::pair<T, int>>& result) const {
    if (root) {
      inorder(root->left, result);
      result.emplace_back(root->key, root->count);
      inorder(root->right, result);
    }
  }

  void delTree(Node* root) {
    if (root) {
      delTree(root->left);
      delTree(root->right);
      delete root;
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { delTree(root); }

  void insert(const T& data) { root = addNode(root, data); }
  int search(T data) const { return searchNode(root, data); }
  int depth() const {
    int fullDepth = depthNode(root);
    return fullDepth > 0 ? fullDepth - 1 : 0;
  }
  void getFreqList(std::vector<std::pair<T, int>>& list) const {
    inorder(root, list);
  }
};

#endif  // INCLUDE_BST_H_
