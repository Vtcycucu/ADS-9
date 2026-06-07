// Copyright 2026 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <cstdint>

struct Node {
    char val;
    int64_t count;
    std::vector<Node*> children;

    explicit Node(char v) : val(v), count(0) {}
    ~Node();
};

class PMTree {
 private:
    Node* root;
    Node* build(char v, std::vector<char> remaining);

 public:
    explicit PMTree(const std::vector<char>& in);
    ~PMTree();
    Node* getRoot() const { return root; }
    int64_t getTotal() const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
