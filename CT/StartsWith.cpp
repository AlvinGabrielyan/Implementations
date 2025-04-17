#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
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
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return true;
    }
};

int main() {
    cout << "Enter the number of words (n): ";
    int n;
    cin >> n;
    
    Trie trie;
    
    cout << "Enter " << n << " words, one per line:" << endl;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        trie.insert(word);
    }
    
    cout << "Enter the number of queries (q): ";
    int q;
    cin >> q;
    
    cout << "Enter " << q << " prefixes to search, one per line:" << endl;
    for (int i = 0; i < q; i++) {
        string prefix;
        cin >> prefix;
        
        if (trie.startsWith(prefix)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
