#include <iostream>
using namespace std;

const bool RED = true;
const bool BLACK = false;

struct Node {
    long long data;
    bool color;
    int size;
    Node* left;
    Node* right;
    Node* parent;

    Node(long long val) : data(val), color(RED), size(1),
                          left(NULL), right(NULL), parent(NULL) {}
};

class RBTree {
private:
    Node* root;

    int getSize(Node* node) {
        return node ? node->size : 0;
    }

    void updateSize(Node* node) {
        if (node) node->size = 1 + getSize(node->left) + getSize(node->right);
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;

        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;

        updateSize(x);
        updateSize(y);
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;

        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;

        y->right = x;
        x->parent = y;

        updateSize(x);
        updateSize(y);
    }

    void insertFixup(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* p = z->parent;
            Node* gp = p->parent;

            if (p == gp->left) {
                Node* y = gp->right;
                if (y && y->color == RED) {
                    p->color = BLACK;
                    y->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } else {
                    if (z == p->right) {
                        z = p;
                        leftRotate(z);
                    }
                    p->color = BLACK;
                    gp->color = RED;
                    rightRotate(gp);
                }
            } else {
                Node* y = gp->left;
                if (y && y->color == RED) {
                    p->color = BLACK;
                    y->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } else {
                    if (z == p->left) {
                        z = p;
                        rightRotate(z);
                    }
                    p->color = BLACK;
                    gp->color = RED;
                    leftRotate(gp);
                }
            }
        }
        root->color = BLACK;
    }

    void insert(Node*& root, Node* z) {
        Node* y = NULL;
        Node* x = root;
        while (x) {
            y = x;
            x->size++; // update size while traversing
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (!y)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;

        insertFixup(z);
    }

    int countLessEqual(Node* node, long long val) {
        if (!node) return 0;
        if (val < node->data)
            return countLessEqual(node->left, val);
        else
            return getSize(node->left) + 1 + countLessEqual(node->right, val);
    }

public:
    RBTree() : root(NULL) {}

    void insert(long long val) {
        Node* z = new Node(val);
        insert(root, z);
    }

    int countInRange(long long l, long long r) {
        return countLessEqual(root, r) - countLessEqual(root, l - 1);
    }
};

int main() {
    RBTree tree;
    int n, op;

    cout << "Enter number of operations: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "1. Insert(value), 2. Count in range [l, r]: ";
        cin >> op;

        if (op == 1) {
            long long val;
            cout << "Enter value to insert: ";
            cin >> val;
            tree.insert(val);
        } else if (op == 2) {
            long long l, r;
            cout << "Enter range [l, r]: ";
            cin >> l >> r;
            int result = tree.countInRange(l, r);
            cout << "Count in range [" << l << ", " << r << "] = " << result << endl;
        } else {
            cout << "Invalid operation." << endl;
        }
    }

    return 0;
}
