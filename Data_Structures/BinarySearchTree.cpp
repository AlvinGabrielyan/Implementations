#include <iostream>
#include <iomanip>
using namespace std;

template <typename NODETYPE>
class Tree; 
template <typename NODETYPE>
class TreeNode {
    friend class Tree<NODETYPE>; 

public:
    TreeNode(const NODETYPE& d) : data{d}, leftPtr{nullptr}, rightPtr{nullptr} {}
    NODETYPE getData() const { return data; }

private:
    NODETYPE data;                        
    TreeNode<NODETYPE>* leftPtr{nullptr}; 
    TreeNode<NODETYPE>* rightPtr{nullptr}; 
};

template <typename NODETYPE>
class Tree {
public:
    void insertNode(const NODETYPE& value) {
        insertNodeHelper(&rootPtr, value);
    }

    bool searchNode(const NODETYPE& value) const {
        return searchNodeHelper(rootPtr, value);
    }

     void deleteNode(const NODETYPE& value) {
        rootPtr = deleteNodeHelper(rootPtr, value);
    }

     void preOrderTraversal() const {
        preOrderHelper(rootPtr);
    }

    void inOrderTraversal() const {
        inOrderHelper(rootPtr);
    }

    void postOrderTraversal() const {
        postOrderHelper(rootPtr);
    }

private:
    TreeNode<NODETYPE>* rootPtr{nullptr};

       void insertNodeHelper(TreeNode<NODETYPE>** ptr, const NODETYPE& value) {
        if (*ptr == nullptr) {
            *ptr = new TreeNode<NODETYPE>(value);
        } else if (value < (*ptr)->data) {
            insertNodeHelper(&((*ptr)->leftPtr), value);
        } else if (value > (*ptr)->data) {
            insertNodeHelper(&((*ptr)->rightPtr), value);
        } else {
            cout << value << " is a duplicate and won't be inserted.\n";
        }
    }

    bool searchNodeHelper(TreeNode<NODETYPE>* ptr, const NODETYPE& value) const {
        if (ptr == nullptr) {
            return false;
        }
        if (value == ptr->data) {
            return true;
        }
        if (value < ptr->data) {
            return searchNodeHelper(ptr->leftPtr, value);
        }
        return searchNodeHelper(ptr->rightPtr, value);
    }

       TreeNode<NODETYPE>* deleteNodeHelper(TreeNode<NODETYPE>* ptr, const NODETYPE& value) {
        if (ptr == nullptr) {
            return nullptr; 
        }

        if (value < ptr->data) {
            ptr->leftPtr = deleteNodeHelper(ptr->leftPtr, value);
        } else if (value > ptr->data) {
            ptr->rightPtr = deleteNodeHelper(ptr->rightPtr, value);
        } else {
            if (ptr->leftPtr == nullptr && ptr->rightPtr == nullptr) { 
                delete ptr;
                return nullptr;
            } else if (ptr->leftPtr == nullptr) {
                TreeNode<NODETYPE>* temp = ptr->rightPtr;
                delete ptr;
                return temp;
            } else if (ptr->rightPtr == nullptr) {
                TreeNode<NODETYPE>* temp = ptr->leftPtr;
                delete ptr;
                return temp;
            } else {
                TreeNode<NODETYPE>* successor = findMin(ptr->rightPtr);
                ptr->data = successor->data;
                ptr->rightPtr = deleteNodeHelper(ptr->rightPtr, successor->data);
            }
        }
        return ptr;
    }

    TreeNode<NODETYPE>* findMin(TreeNode<NODETYPE>* ptr) const {
        while (ptr->leftPtr != nullptr) {
            ptr = ptr->leftPtr;
        }
        return ptr;
    }

    void preOrderHelper(TreeNode<NODETYPE>* ptr) const {
        if (ptr != nullptr) {
            cout << ptr->data << ' ';
            preOrderHelper(ptr->leftPtr);
            preOrderHelper(ptr->rightPtr);
        }
    }

    void inOrderHelper(TreeNode<NODETYPE>* ptr) const {
        if (ptr != nullptr) {
            inOrderHelper(ptr->leftPtr);
            cout << ptr->data << ' ';
            inOrderHelper(ptr->rightPtr);
        }
    }

    void postOrderHelper(TreeNode<NODETYPE>* ptr) const {
        if (ptr != nullptr) {
            postOrderHelper(ptr->leftPtr);
            postOrderHelper(ptr->rightPtr);
            cout << ptr->data << ' ';
        }
    }
};

int main() {
    Tree<int> intTree;

    cout << "Enter 10 integer values to insert:\n";
    for (int i = 0; i < 10; ++i) {
        int value;
        cin >> value;
        intTree.insertNode(value);
    }

    cout << "\nPreorder traversal:\n";
    intTree.preOrderTraversal();

    cout << "\n\nInorder traversal:\n";
    intTree.inOrderTraversal();

    cout << "\n\nPostorder traversal:\n";
    intTree.postOrderTraversal();

    int searchValue;
    cout << "\n\nEnter a value to search for:\n";
    cin >> searchValue;
    if (intTree.searchNode(searchValue)) {
        cout << searchValue << " is in the tree.\n";
    } else {
        cout << searchValue << " is not in the tree.\n";
    }

    int deleteValue;
    cout << "Enter a value to delete:\n";
    cin >> deleteValue;
    intTree.deleteNode(deleteValue);

    cout << "\n\nPreorder traversal after deletion:\n";
    intTree.preOrderTraversal();

    cout << "\n\nInorder traversal after deletion:\n";
    intTree.inOrderTraversal();

    cout << "\n\nPostorder traversal after deletion:\n";
    intTree.postOrderTraversal();

    return 0;
}
