#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "tree.h"

Node::~Node() {
    for (Node* child : children) {
        delete child;
    }
}

int64_t PMTree::getTotal() const {
    return root ? root->count : 0;
}

Node* PMTree::build(char v, std::vector<char> remaining) {
    Node* node = new Node(v);
    if (remaining.empty()) {
        node->count = 1;
        return node;
    }
    for (size_t i = 0; i < remaining.size(); ++i) {
        std::vector<char> next_rem;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (i != j) {
                next_rem.push_back(remaining[j]);
            }
        }
        Node* child = build(remaining[i], next_rem);
        node->children.push_back(child);
    }
    node->count = node->children.size() * node->children[0]->count;
    return node;
}

PMTree::PMTree(const std::vector<char>& in) : root(nullptr) {
    if (in.empty()) return;
    std::vector<char> sorted = in;
    std::sort(sorted.begin(), sorted.end());
    root = new Node('\0');
    for (size_t i = 0; i < sorted.size(); ++i) {
        std::vector<char> remaining;
        for (size_t j = 0; j < sorted.size(); ++j) {
            if (i != j) {
                remaining.push_back(sorted[j]);
            }
        }
        Node* child = build(sorted[i], remaining);
        root->children.push_back(child);
    }
    if (!root->children.empty()) {
        root->count = root->children.size() * root->children[0]->count;
    }
}

PMTree::~PMTree() {
    delete root;
}

void collectDFS(Node* node, std::vector<char>& path, std::vector<std::vector<char>>& res, bool isRoot) {
    if (!isRoot) {
        path.push_back(node->val);
    }
    if (node->children.empty()) {
        res.push_back(path);
    } else {
        for (Node* child : node->children) {
            collectDFS(child, path, res, false);
        }
    }
    if (!isRoot) {
        path.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> res;
    Node* root = tree.getRoot();
    if (!root) return res;
    std::vector<char> path;
    collectDFS(root, path, res, true);
    return res;
}

bool findDFS(Node* node, std::vector<char>& path, int& current_num, int target_num, bool isRoot, std::vector<char>& res) {
    if (!isRoot) {
        path.push_back(node->val);
    }
    if (node->children.empty()) {
        current_num++;
        if (current_num == target_num) {
            res = path;
            if (!isRoot) path.pop_back();
            return true;
        }
    } else {
        for (Node* child : node->children) {
            if (findDFS(child, path, current_num, target_num, false, res)) {
                if (!isRoot) path.pop_back();
                return true;
            }
        }
    }
    if (!isRoot) {
        path.pop_back();
    }
    return false;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num < 1) return {};
    Node* root = tree.getRoot();
    if (!root || root->count < num) return {};
    std::vector<char> path, res;
    int current_num = 0;
    findDFS(root, path, current_num, num, true, res);
    return res;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num < 1) return {};
    Node* root = tree.getRoot();
    if (!root || root->count < num) return {};
    std::vector<char> res;
    Node* curr = root;
    int64_t target = num;
    while (!curr->children.empty()) {
        int64_t step = curr->children[0]->count;
        int64_t idx = (target - 1) / step;
        Node* next = curr->children[idx];
        res.push_back(next->val);
        target = (target - 1) % step + 1;
        curr = next;
    }
    return res;
}
