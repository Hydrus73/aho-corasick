/**
 * Basic Aho-Corasick implementation with suffix and dictionary links.
 * You can also store additional data with a custom class as a template parameter.
 *
 * This implementation works with any characters.
 *
 * @author Ben MacDougall
 */
#include <bits/stdc++.h>
template <typename ExtraData>
class AhoCorasick {
   public:
    class Node {
       public:
        std::vector<Node*> children, transitions;
        Node* parent;
        Node* suffix_link;
        Node* dictionary_link;
        bool computed_dictionary_link;
        bool is_word_end;
        int depth;
        Node* root;
        char character;
        ExtraData data;
        Node(Node* parent, bool is_word_end, int depth, Node* root, char character) {
            this->is_word_end = is_word_end;
            this->parent = parent;
            this->depth = depth;
            this->root = root;
            this->character = character;
            children = std::vector<Node*>(256, nullptr);
            transitions = std::vector<Node*>(256, nullptr);
            suffix_link = nullptr;
            dictionary_link = nullptr;
            computed_dictionary_link = false;
        }
        Node* get_suffix_link() {
            if (suffix_link == nullptr) {
                if (parent == root) {
                    suffix_link = root;
                } else {
                    suffix_link = parent->get_suffix_link()->transition(character);
                }
            }
            return suffix_link;
        }
        Node* get_dictionary_link() {
            if (root != this && !computed_dictionary_link) {
                if (get_suffix_link()->is_word_end) {
                    dictionary_link = get_suffix_link();
                } else if (get_suffix_link() != root) {
                    dictionary_link = get_suffix_link()->get_dictionary_link();
                }
            }
            computed_dictionary_link = true;
            return dictionary_link;
        }
        Node* transition(char character) {
            if (transitions[character] == nullptr) {
                if (children[character] != nullptr) {
                    transitions[character] = children[character];
                } else if (root == this) {
                    transitions[character] = this;
                } else {
                    transitions[character] = get_suffix_link()->transition(character);
                }
            }
            return transitions[character];
        }
    };
    Node* root;
    Node* insert(std::string& word, Node* current = nullptr, int depth = 0) {
        if (current == nullptr) {
            current = root;
        }
        if (current->children[word[depth]] == nullptr) {
            current->children[word[depth]] = new Node(current, depth == word.length() - 1, depth + 1, root, word[depth]);
        }
        if (depth == word.length() - 1) {
            current->children[word[depth]]->is_word_end = true;
            return current->children[word[depth]];
        }
        return insert(word, current->children[word[depth]], depth + 1);
    }
    AhoCorasick() {
        root = new Node(nullptr, false, 0, nullptr, '\0');
        root->root = root;
        root->parent = root;
    }
};