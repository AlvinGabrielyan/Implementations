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
    else if (k > p->key)
        p->right = insert(p->right, k);
    else 
        return p; 
    
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
    else {
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

void printTree(Node* root, string indent = "", char position = ' ') {
    if (root) {
        cout << indent;
        if (position != ' ') {
            cout << "(" << position << ") ";
        }
        cout << root->key << " (h=" << (int)root->height << ", bf=" << bfactor(root) << ")\n";
        
        printTree(root->left, indent + "    ", 'L');
        printTree(root->right, indent + "    ", 'R');
    }
}

void deleteTree(Node* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main() {
    Node* root = nullptr;
    int choice, value;

    while (true) {
        cout << "\n1. Insert\n2. Delete\n3. Print Tree\n4. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = remove(root, value);
                break;
            case 3:
                cout << "\nTree Structure:\n";
                printTree(root);
                break;t
            case 4:
                deleteTree(root);
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
