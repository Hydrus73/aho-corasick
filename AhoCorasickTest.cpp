#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <bits/stdc++.h>

#include "AhoCorasick.h"
#include "doctest.h"
TEST_CASE("Testing the Aho-Corasick algorithm") {
    AhoCorasick<int> ahoCorasick;
    CHECK(ahoCorasick.root->get_suffix_link() == ahoCorasick.root);
    std::string word1 = "abc";
    ahoCorasick.insert(word1);
    std::string word2 = "cabc";
    ahoCorasick.insert(word2);
    std::string word3 = "bcabc";
    ahoCorasick.insert(word3);
    AhoCorasick<int>::Node* root = ahoCorasick.root;
    SUBCASE("Testing the suffix links") {
        CHECK(root->children['a']->get_suffix_link() == root);
        CHECK(root->children['a']->children['b']->get_suffix_link() == root->children['b']);
        CHECK(root->children['a']->children['b']->children['c']->get_suffix_link() == root->children['b']->children['c']);
        CHECK(root->children['b']->get_suffix_link() == root);
        CHECK(root->children['b']->children['c']->get_suffix_link() == root->children['c']);
        CHECK(root->children['b']->children['c']->children['a']->get_suffix_link() == root->children['c']->children['a']);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->get_suffix_link() == root->children['c']->children['a']->children['b']);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->children['c']->get_suffix_link() == root->children['c']->children['a']->children['b']->children['c']);
        CHECK(root->children['c']->get_suffix_link() == root);
        CHECK(root->children['c']->children['a']->get_suffix_link() == root->children['a']);
        CHECK(root->children['c']->children['a']->children['b']->get_suffix_link() == root->children['a']->children['b']);
        CHECK(root->children['c']->children['a']->children['b']->children['c']->get_suffix_link() == root->children['a']->children['b']->children['c']);
    }
    SUBCASE("Testing the dictionary links") {
        std::string word4 = "a";
        ahoCorasick.insert(word4);
        CHECK(root->children['a']->get_dictionary_link() == nullptr);
        CHECK(root->children['a']->children['b']->get_dictionary_link() == nullptr);
        CHECK(root->children['a']->children['b']->children['c']->get_dictionary_link() == nullptr);
        CHECK(root->children['b']->get_dictionary_link() == nullptr);
        CHECK(root->children['b']->children['c']->get_dictionary_link() == nullptr);
        CHECK(root->children['b']->children['c']->children['a']->get_dictionary_link() == root->children['a']);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->get_dictionary_link() == nullptr);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->children['c']->get_dictionary_link() == root->children['c']->children['a']->children['b']->children['c']);
        CHECK(root->children['c']->get_dictionary_link() == nullptr);
        CHECK(root->children['c']->children['a']->get_dictionary_link() == root->children['a']);
        CHECK(root->children['c']->children['a']->children['b']->get_dictionary_link() == nullptr);
        CHECK(root->children['c']->children['a']->children['b']->children['c']->get_dictionary_link() == root->children['a']->children['b']->children['c']);
    }
    SUBCASE("Testing transitions") {
        AhoCorasick<int>::Node* current = root;
        current = current->transition('a');
        CHECK(current == root->children['a']);
        current = current->transition('b');
        CHECK(current == root->children['a']->children['b']);
        current = current->transition('c');
        CHECK(current == root->children['a']->children['b']->children['c']);
        current = current->transition('a');
        CHECK(current == root->children['b']->children['c']->children['a']);
        current = current->transition('b');
        CHECK(current == root->children['b']->children['c']->children['a']->children['b']);
        current = current->transition('c');
        CHECK(current == root->children['b']->children['c']->children['a']->children['b']->children['c']);
        current = current->transition('a');
        CHECK(current == root->children['b']->children['c']->children['a']);
        current = current->transition('d');
        CHECK(current == root);
        current = current->transition('e');
        CHECK(current == root);
        current = current->transition('a');
        CHECK(current == root->children['a']);
    }
    SUBCASE("Testing word ends") {
        CHECK(root->children['a']->children['b']->children['c']->is_word_end == true);
        CHECK(root->children['c']->children['a']->children['b']->children['c']->is_word_end == true);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->children['c']->is_word_end == true);
        CHECK(root->children['a']->children['b']->is_word_end == false);
        CHECK(root->children['c']->children['a']->children['b']->is_word_end == false);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->is_word_end == false);
        CHECK(root->children['a']->children['b']->children['c']->depth == 3);
        CHECK(root->children['c']->children['a']->children['b']->children['c']->depth == 4);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->children['c']->depth == 5);
        CHECK(root->children['a']->children['b']->depth == 2);
        CHECK(root->children['c']->children['a']->children['b']->depth == 3);
        CHECK(root->children['b']->children['c']->children['a']->children['b']->depth == 4);
    }
}