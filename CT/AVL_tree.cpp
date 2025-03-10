#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    unsigned char height;
    Node* left;
    Node* right;
    
    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(Node* p) {
    return p ? p->height : 0;
}

int bfactor(Node* p) {
    return height(p->right) - height(p->left);
}

void fixheight(Node* p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateright(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Node* rotateleft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

Node* balance(Node* p) {
    fixheight(p);
    
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    
    return p; 
}

Node* insert(Node* p, int k) {
    if (!p) return new Node(k);
    
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    
    return balance(p);
}

Node* findmin(Node* p) {
    return p->left ? findmin(p->left) : p;
}

Node* removemin(Node* p) {
    if (!p->left)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

Node* remove(Node* p, int k) {
    if (!p) return nullptr;
    
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else { // k == p->key
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r) return q;
        
        Node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    
    return balance(p);
}

void printInOrder(Node* root) {
    if (root) {
        printInOrder(root->left);
        cout << root->key << " ";
        printInOrder(root->right);
    }
}

void printTree(Node* root, string indent = "", bool last = true) {
    if (root) {
        cout << indent;
        cout << (last ? "└── " : "├── ");
        cout << root->key << " (h=" << (int)root->height << ", bf=" << bfactor(root) << ")" << endl;
        
        indent += last ? "    " : "│   ";
        
        printTree(root->left, indent, !root->right);
        if (root->right) {
            printTree(root->right, indent, true);
        }
    }
}

void deleteTree(Node* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void solveProblem1() {
    cout << "\n--- Problem 1: Inserting decreasing sequence ---\n";
    Node* root = nullptr;
    
    cout << "Inserting 50\n";
    root = insert(root, 50);
    printTree(root);
    
    cout << "\nInserting 40\n";
    root = insert(root, 40);
    printTree(root);
    
    cout << "\nInserting 30 (should trigger right rotation at 50)\n";
    root = insert(root, 30);
    printTree(root);
    
    deleteTree(root);
}

void solveProblem2() {
    cout << "\n--- Problem 2: Inserting nodes with LL-rotation ---\n";
    Node* root = nullptr;
    vector<int> keys = {60, 50, 70, 40, 55, 30};
    
    for (int i = 0; i < keys.size(); i++) {
        cout << "\nInserting " << keys[i];
        if (keys[i] == 30) cout << " (should trigger right rotation at 50)";
        cout << "\n";
        
        root = insert(root, keys[i]);
        printTree(root);
    }
    
    deleteTree(root);
}

void solveProblem3() {
    cout << "\n--- Problem 3: Multiple LL rotations in large tree ---\n";
    Node* root = nullptr;
    vector<int> keys = {100, 90, 80, 70, 60, 50};
    
    for (int i = 0; i < keys.size(); i++) {
        cout << "\nInserting " << keys[i];
        if (keys[i] == 80) cout << " (should trigger right rotation at 100)";
        if (keys[i] == 70) cout << " (should trigger right rotation at 90)";
        if (keys[i] == 60) cout << " (should trigger right rotation at 80)";
        cout << "\n";
        
        root = insert(root, keys[i]);
        printTree(root);
    }
    
    deleteTree(root);
}

int main() {
    solveProblem1();
    solveProblem2();
    solveProblem3();
    
    return 0;
}
