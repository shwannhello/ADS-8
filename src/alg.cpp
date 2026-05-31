// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if ((ch >= 'a' && ch <= 'z') ||
          (ch >= 'A' && ch <= 'Z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + ('a' - 'A');
            }
            word += ch;
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freqList;
    tree.getFreqList(freqList);

    std::sort(freqList.begin(), freqList.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    for (const auto& pair : freqList) {
        std::cout << pair.first << " "
          << pair.second << std::endl;
    }

    std::ofstream outFile("result/freq.txt");
    if (outFile) {
        for (const auto& pair : freqList) {
            outFile << pair.first << " "
              << pair.second << std::endl;
        }
        outFile.close();
    } else {
        std::cout << "Error opening result file for writing!" << std::endl;
    }
}
