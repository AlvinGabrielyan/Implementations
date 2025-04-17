#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    void findAllWordsHelper(TrieNode* node, string currentWord, vector<string>& result) {
        if (node->isEndOfWord) {
            result.push_back(currentWord);
        }

        for (auto& pair : node->children) {
            char ch = pair.first;
            TrieNode* child = pair.second;
            findAllWordsHelper(child, currentWord + ch, result);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }
    
    void deleteTrie(TrieNode* node) {
        for (auto& p : node->children) {
            deleteTrie(p.second);
        }
        delete node;
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children[ch]) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children[ch]) return false;
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }

    void remove(const string& word) {
        removeHelper(root, word, 0);
    }

    bool removeHelper(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) return false;
            node->isEndOfWord = false;
            return node->children.empty();
        }
        char ch = word[index];
        if (node->children.find(ch) == node->children.end()) 
            return false;
        TrieNode* child = node->children[ch];
        bool shouldDeleteChild = removeHelper(child, word, index + 1);
        if (shouldDeleteChild) {
            delete child;
            node->children.erase(ch);
            return node->children.empty() && !node->isEndOfWord;
        }
        return false;
    }

    void printTrie() {
        printTrieHelper(root, "", "");
    }

    void printTrieHelper(TrieNode* node, string prefix, string output) {
        if (output == "") {
            cout << "(root)" << endl;
        } else {
            cout << prefix << output;
            if (node->isEndOfWord) cout << " (end)";
            cout << endl;
        }
        for (auto& p : node->children) {
            printTrieHelper(p.second, prefix + "  ", string(1, p.first));
        }
    }

    vector<string> findAllWords() {
        vector<string> result;
        findAllWordsHelper(root, "", result);
        return result;
    }

    vector<string> findShortestWords() {
        vector<string> allWords = findAllWords();
        if (allWords.empty()) {
            return {};
        }

        size_t minLength = allWords[0].length();
        for (const string& word : allWords) {
            minLength = min(minLength, word.length());
        }

        vector<string> shortestWords;
        for (const string& word : allWords) {
            if (word.length() == minLength) {
                shortestWords.push_back(word);
            }
        }

        return shortestWords;
    }

    vector<string> findLongestWords() {
        vector<string> allWords = findAllWords();
        if (allWords.empty()) {
            return {};
        }

        size_t maxLength = 0;
        for (const string& word : allWords) {
            maxLength = max(maxLength, word.length());
        }

        vector<string> longestWords;
        for (const string& word : allWords) {
            if (word.length() == maxLength) {
                longestWords.push_back(word);
            }
        }

        return longestWords;
    }
};

int main() {
    Trie trie;
    int choice;
    string word;
    while (true) {
        cout << "\n--- Trie Menu ---\n";
        cout << "1. Insert word\n";
        cout << "2. Search word\n";
        cout << "3. Delete word\n";
        cout << "4. Print trie structure\n";
        cout << "5. Find shortest words\n";
        cout << "6. Find longest words\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter word to insert: ";
            cin >> word;
            trie.insert(word);
            cout << "Inserted.\n";
            break;
        case 2:
            cout << "Enter word to search: ";
            cin >> word;
            if (trie.search(word))
                cout << "Found!\n";
            else
                cout << "Not found.\n";
            break;
        case 3:
            cout << "Enter word to delete: ";
            cin >> word;
            trie.remove(word);
            cout << "Deleted (if existed).\n";
            break;
        case 4:
            cout << "Trie structure:\n";
            trie.printTrie();
            break;
        case 5:
            {
                vector<string> shortestWords = trie.findShortestWords();
                if (shortestWords.empty()) {
                    cout << "No words in the trie.\n";
                } else {
                    cout << "Shortest words:\n";
                    for (const string& word : shortestWords) {
                        cout << "- " << word << " (length: " << word.length() << ")\n";
                    }
                }
            }
            break;
        case 6:
            {
                vector<string> longestWords = trie.findLongestWords();
                if (longestWords.empty()) {
                    cout << "No words in the trie.\n";
                } else {
                    cout << "Longest words:\n";
                    for (const string& word : longestWords) {
                        cout << "- " << word << " (length: " << word.length() << ")\n";
                    }
                }
            }
            break;
        case 7:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
