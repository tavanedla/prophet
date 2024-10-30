#ifndef TRIE_
#define TRIE_

#include <memory>

namespace prophet {

struct TrieNode {
    std::unique_ptr<TrieNode> children[2];

    bool IsLeaf() const {
        return children[0] == nullptr && children[1] == nullptr;
    }

    bool hasChild(int child) const {
        return children[child] != nullptr;
    }

    bool Empty() {
        return children[0] == nullptr && children[1] == nullptr;
    }
};

class BinaryTrie {
    public:
        // Insert a value formed `len` number of leading bits from given `ip_addr`.
        void Insert(const std::string& binary_ip);

        // Return true if the Trie contains some prefix of the given ip. False otherwise.
        bool HasPrefix(const std::string& binary_ip) const;

        // Erase a value formed by `len` number of leading bits of `ip_addr` if it exists.
        // Returns true if the value was found and erased, false if it was not found.
        bool Erase(const std::string& binary_ip);
   
    private:
        TrieNode* find(const std::string& binary_ip);
        bool recursiveDelete(TrieNode* cur_node, std::string_view binary_ip);
        TrieNode root_;
};

} // namespace prophet

#endif