#include <iostream>
#include <string>
#include <unordered_map>
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
        cout << "5. Exit\n";
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
            cout << "Goodbye!\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
