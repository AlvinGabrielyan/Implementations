#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Interval {
    int low, high;
    Interval(int l, int h) : low(l), high(h) {}
};

struct Node {
    int key;                       
    bool isRed;                    
    Node *left, *right;          
    int size;                   
    int sum;                     
    int maxHigh;             
    Interval interval;          
    
    Node(int k) : key(k), isRed(true), left(nullptr), right(nullptr), 
                 size(1), sum(k), maxHigh(0), interval(0, 0) {}
    
    
    Node(Interval i) : key(i.low), isRed(true), left(nullptr), right(nullptr),
                      size(1), sum(i.low), maxHigh(i.high), interval(i) {}
};

class RBTree {
private:
    Node* root;

    // TASK 1: Height calculation
    int height(Node* node) {
        if (!node) return -1;
        return 1 + max(height(node->left), height(node->right));
    }

    // TASK 2: RB Tree validity check
    bool isValid(Node* node, int& blackHeight, bool parentRed) {
        
        if (!node) {
            blackHeight = 1;
            return true;
        }
        
        if (parentRed && node->isRed)
            return false;
            
        int leftBlackHeight = 0, rightBlackHeight = 0;
        
        if (!isValid(node->left, leftBlackHeight, node->isRed)) 
            return false;
            
        if (!isValid(node->right, rightBlackHeight, node->isRed)) 
            return false;
            
        if (leftBlackHeight != rightBlackHeight)
            return false; 
            
        blackHeight = leftBlackHeight + (node->isRed ? 0 : 1);
        return true;
    }

    // TASK 3 & 5: Update size and sum after changes
    void updateSizeAndSum(Node* node) {
        if (node) {
            node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
            node->sum = node->key + (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0);
        }
    }

    // TASK 3 & 5: Range counting and summing
    int countInRange(Node* node, int low, int high) {
        if (!node) return 0;
        
        // If current node is outside the range, skip the subtree
        if (node->key < low) return countInRange(node->right, low, high);
        if (node->key > high) return countInRange(node->left, low, high);
        
        return 1 + countInRange(node->left, low, high) + countInRange(node->right, low, high);
    }

    int sumInRange(Node* node, int low, int high) {
        if (!node) return 0;
        
        // If current node is outside the range, skip the subtree
        if (node->key < low) return sumInRange(node->right, low, high);
        if (node->key > high) return sumInRange(node->left, low, high);
        
        // Node is within range, sum left, right, and itself
        return node->key + sumInRange(node->left, low, high) + sumInRange(node->right, low, high);
    }

    // TASK 4: Inorder traversal helper
    void inorderHelper(Node* node) {
        if (node) {
            inorderHelper(node->left);
            cout << node->key << " ";
            inorderHelper(node->right);
        }
    }

    // TASK 6: Kth smallest element helper
    Node* kth(Node* node, int k) {
        if (!node) return nullptr;
        
        int leftSize = (node->left) ? node->left->size : 0;
        
        if (k == leftSize + 1)
            return node;
        else if (k <= leftSize)
            return kth(node->left, k);
        else
            return kth(node->right, k - leftSize - 1);
    }

    // TASK 6: Rank helper (number of elements < x)
    int rank(Node* node, int x) {
        if (!node) return 0;
        
        if (x <= node->key)
            return rank(node->left, x);
        else {
            int leftSize = (node->left) ? node->left->size : 0;
            return 1 + leftSize + rank(node->right, x);
        }
    }

    // TASK 6: Fix sizes recursively
    void fixSizes(Node* node) {
        if (!node) return;
        fixSizes(node->left);
        fixSizes(node->right);
        updateSizeAndSum(node);
    }

    // TASK 7: Update maxHigh for interval tree
    void updateMax(Node* node) {
        if (!node) return;
        
        node->maxHigh = node->interval.high;
        
        if (node->left && node->left->maxHigh > node->maxHigh)
            node->maxHigh = node->left->maxHigh;
            
        if (node->right && node->right->maxHigh > node->maxHigh)
            node->maxHigh = node->right->maxHigh;
    }

    // TASK 7: Check if two intervals overlap
    bool isOverlap(Interval a, Interval b) {
        return a.low <= b.high && b.low <= a.high;
    }

    // TASK 7: Search for all overlapping intervals
    void search(Node* node, Interval q, vector<Interval>& result) {
        if (!node) return;
        
        if (isOverlap(node->interval, q)) {
            result.push_back(node->interval);
        }
        
        if (node->left && node->left->maxHigh >= q.low) {
            search(node->left, q, result);
        }
        
        if (node->right && node->interval.low <= q.high) {
            search(node->right, q, result);
        }
    }

    // TASK 7: Update maxHigh recursively
    void updateMaxRecursively(Node* node) {
        if (!node) return;
        updateMaxRecursively(node->left);
        updateMaxRecursively(node->right);
        updateMax(node);
    }

public:
    RBTree() : root(nullptr) {}

    // TASK 1: Set root and get height
    void setRoot(Node* r) { 
        root = r; 
        fixSizes(root);            // Fix size properties for all nodes
        updateMaxRecursively(root); // Update maxHigh for interval functionality
    }
    
    int getHeight() { 
        return height(root); 
    }

    // TASK 2: Check if tree is valid RB tree
    bool isValidRBTree() {
        if (!root) return true;
        if (root->isRed) return false; // Root must be black
        int bh = 0;
        return isValid(root, bh, false);
    }

    // TASK 3 & 5: Range queries
    int countRange(int low, int high) {
        return countInRange(root, low, high);
    }
    
    int sumRange(int low, int high) {
        return sumInRange(root, low, high);
    }

    // TASK 4: In-order traversal
    void inorderTraversal() {
        inorderHelper(root);
        cout << endl;
    }

    // TASK 6: Kth smallest and rank operations
    int kthSmallest(int k) {
        Node* res = kth(root, k);
        return res ? res->key : -1;
    }
    
    // TASK 6: Select operation (renamed to match required API)
    int select(int k) {
        Node* res = kth(root, k);
        return res ? res->key : -1;
    }
    
    int getRank(int x) {
        return rank(root, x);
    }

    // TASK 7: Find overlapping intervals
    vector<Interval> findOverlaps(Interval query) {
        vector<Interval> result;
        search(root, query, result);
        return result;
    }
};

// Helper to print intervals (Task 7)
void printIntervals(const vector<Interval>& intervals) {
    for (const auto& iv : intervals)
        cout << "[" << iv.low << ", " << iv.high << "] ";
    cout << endl;
}

// Unified driver function demonstrating all features
int main() {
    cout << "===== Merged Red-Black Tree Demo =====" << endl << endl;
    
    // Create a regular RB tree
    cout << "Creating a regular Red-Black Tree..." << endl;
    RBTree tree;
    
    Node* root = new Node(9);
    root->isRed = false; // BLACK
    root->left = new Node(4);
    root->right = new Node(14);
    root->left->isRed = true;  // RED
    root->right->isRed = true; // RED
    root->left->left = new Node(2);
    root->left->left->isRed = false;
    root->left->right = new Node(6);
    root->left->right->isRed = false;
    
    tree.setRoot(root);
    
    // TASK 1: Height calculation
    cout << "TASK 1: Height of the tree: " << tree.getHeight() << endl;
    
    // TASK 2: Validity check
    cout << "TASK 2: Is valid RB tree? " << (tree.isValidRBTree() ? "Yes" : "No") << endl;
    
    // TASK 3 & 5: Range queries
    cout << "TASK 3 & 5: Count in range [5, 15]: " << tree.countRange(5, 15) << endl;
    cout << "TASK 3 & 5: Sum in range [5, 15]: " << tree.sumRange(5, 15) << endl;
    
    // TASK 4: In-order traversal
    cout << "TASK 4: In-order traversal: ";
    tree.inorderTraversal();
    
    // TASK 6: Kth smallest and rank
    cout << "TASK 6: 1st smallest: " << tree.kthSmallest(1) << endl;
    cout << "TASK 6: 3rd smallest: " << tree.kthSmallest(3) << endl;
    cout << "TASK 6: Select(2): " << tree.select(2) << endl; 
    cout << "TASK 6: Rank of 10: " << tree.getRank(10) << endl;
    
    // Create an interval tree (Task 7)
    cout << "\nCreating an Interval Tree..." << endl;
    RBTree intervalTree;
    
    Node* intervalRoot = new Node(Interval(15, 20));
    intervalRoot->isRed = false;
    intervalRoot->left = new Node(Interval(10, 30));
    intervalRoot->left->isRed = true;
    intervalRoot->right = new Node(Interval(17, 19));
    intervalRoot->right->isRed = true;
    intervalRoot->left->left = new Node(Interval(5, 20));
    intervalRoot->left->left->isRed = false;
    intervalRoot->left->right = new Node(Interval(12, 15));
    intervalRoot->left->right->isRed = false;
    intervalRoot->right->right = new Node(Interval(30, 40));
    intervalRoot->right->right->isRed = false;
    
    intervalTree.setRoot(intervalRoot);
    
    // TASK 7: Find overlapping intervals
    Interval query(14, 16);
    vector<Interval> result = intervalTree.findOverlaps(query);
    cout << "TASK 7: Overlapping intervals with [14, 16]: ";
    printIntervals(result);
    
    return 0;
}
