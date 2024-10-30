#include "trie.h"

#include <iostream>

namespace prophet {

void BinaryTrie::Insert(const std::string& binary_ip) {
    std::cout << "Inserting range : " << binary_ip << std::endl;
    auto* cur_node = &root_;
    for (int i = 0; i < binary_ip.size(); i++) {
        char cur_bit = binary_ip[i] - '0';
        if (cur_node->hasChild(cur_bit)) {
            cur_node = cur_node->children[cur_bit].get();
        } else {
            cur_node->children[cur_bit] = std::make_unique<TrieNode>();
            cur_node = cur_node->children[cur_bit].get();
        }
    }
    std::cout << std::endl;
    cur_node->children[0] = nullptr;
    cur_node->children[1] = nullptr;
}

bool BinaryTrie::HasPrefix(const std::string& binary_ip) const {
    auto* cur_node = &root_;

    std::cout << "Checking for ip : " << binary_ip << std::endl;
    for (int i = 0; i < binary_ip.size(); i++) {
        auto cur_bit =  binary_ip[i] - '0';

        if (cur_node->hasChild(cur_bit)) {
            cur_node = cur_node->children[cur_bit].get();
        } else {
            return false;
        }

        if (cur_node->IsLeaf()) return true;
    }
    return false;
}

bool BinaryTrie::Erase(const std::string& binary_ip) {
    std::cout << "Trying to erase : " << binary_ip << std::endl;
    return recursiveDelete(&root_, binary_ip);
}

TrieNode* BinaryTrie::find(const std::string& binary_ip) {
    auto* cur_node = &root_;
    for (auto c : binary_ip) {
        uint cur_bit = c - '0';
        if (cur_node->hasChild(cur_bit)) {
            cur_node = cur_node->children[cur_bit].get();
        } else {
            return nullptr;
        }
    }
    return cur_node;
}

bool BinaryTrie::recursiveDelete(TrieNode* cur_node, std::string_view binary_ip) {
    if (binary_ip.size() == 1) {
        cur_node->children[0].reset();
        cur_node->children[1].reset();
        return true;
    }

    uint cur_bit = binary_ip[0] - '0';
    if (cur_node->hasChild(cur_bit)) {
        bool deleted = recursiveDelete(cur_node->children[cur_bit].get(), binary_ip.substr(1));
        if (cur_node->children[cur_bit]->Empty()) {
            cur_node->children[cur_bit].reset();
        }
        return deleted;
    } else {
        return false;
    }
}

} // namespace prophet