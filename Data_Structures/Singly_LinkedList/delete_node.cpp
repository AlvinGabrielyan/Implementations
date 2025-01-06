#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void deleteNode(Node* node) {
    if (node == nullptr || node->next == nullptr) {
        cout << "Node cannot be deleted using this method!" << endl;
        return;
    }

    Node* nextNode = node->next;
    node->data = nextNode->data;

    node->next = nextNode->next;

    delete nextNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

Node* createList() {
    Node* head = nullptr;
    Node* current = nullptr;

    int value;
    char choice;

    do {
        cout << "Enter node value: ";
        cin >> value;
        
        Node* newNode = new Node{value, nullptr};

        if (head == nullptr) {
            head = newNode;  
        } else {
            current->next = newNode; 
        }

        current = newNode; 

        cout << "Do you want to add another node? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return head;
}

Node* findNode(Node* head, int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr; 
}

int main() {
    Node* head = createList();

    cout << "Original list: ";
    printList(head);

    int valueToDelete;
    cout << "Enter the value of the node to delete: ";
    cin >> valueToDelete;

    Node* nodeToDelete = findNode(head, valueToDelete);

    if (nodeToDelete != nullptr) {
        deleteNode(nodeToDelete);
        cout << "After deletion: ";
        printList(head);
    } else {
        cout << "Node with value " << valueToDelete << " not found." << endl;
    }

    return 0;
}
