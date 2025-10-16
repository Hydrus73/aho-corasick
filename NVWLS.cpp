/**
 * This solution to the NVWLS problem uses my implementation of the Aho-Corasick data structure.
 * 
 * https://open.kattis.com/problems/nvwls
 *
 * @author Ben MacDougall
 */
#include <bits/stdc++.h>

#include "AhoCorasick.h"
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string vowels = "AEIOU";
    AhoCorasick<int> ahoCorasick;
    int total_words;
    std::cin >> total_words;
    std::vector<std::string> words(total_words);
    for (int i = 0; i < total_words; i++) {
        std::cin >> words[i];
    }
    std::unordered_map<std::string, std::string> no_vowel_to_word;
    for (std::string s : words) {
        std::string no_vowel = "";
        for (char c : s) {
            if (vowels.find(c) == std::string::npos) {
                no_vowel += c;
            }
        }
        if (no_vowel_to_word.find(no_vowel) == no_vowel_to_word.end() || no_vowel_to_word[no_vowel].length() < s.length()) {
            no_vowel_to_word[no_vowel] = s;
        }
    }
    for (std::pair<std::string, std::string> p : no_vowel_to_word) {
        int vowel_count = p.second.length() - p.first.length();
        ahoCorasick.insert(p.first)->data = vowel_count;
    }
    std::string no_vowel_message;
    std::cin >> no_vowel_message;
    std::vector<int> dp(no_vowel_message.length() + 1, -1);
    std::vector<int> parent(no_vowel_message.length() + 1, 0);
    dp[0] = 0;
    parent[0] = -1;
    auto current = ahoCorasick.root;
    for (int i = 0; i < no_vowel_message.length(); i++) {
        current = current->transition(no_vowel_message[i]);
        for (auto node = current; node != nullptr; node = node->get_dictionary_link()) {
            if (node->is_word_end) {
                int start = i - node->depth + 1;
                if (dp[start] != -1 && dp[i + 1] < dp[start] + node->data) {
                    dp[i + 1] = dp[start] + node->data;
                    parent[i + 1] = start;
                }
            }
        }
    }
    std::vector<std::string> words_reversed;
    int index = no_vowel_message.length();
    while (parent[index] != -1) {
        std::string word = no_vowel_message.substr(parent[index], index - parent[index]);
        words_reversed.push_back(no_vowel_to_word[word]);
        index = parent[index];
    }
    for (int i = words_reversed.size() - 1; i >= 0; i--) {
        if (i == 0) {
            std::cout << words_reversed[i] << std::endl;
        } else {
            std::cout << words_reversed[i] << " ";
        }
    }
}