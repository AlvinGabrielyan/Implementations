#include <iostream>
using namespace std;

class ListNode 
{
public:
    ListNode(const double value, ListNode* next = nullptr, ListNode* prev = nullptr)
        : _data(value), _nextPtr(next), _prevPtr(prev) {}

    double _data;
    ListNode* _nextPtr; 
    ListNode* _prevPtr;
};

class List { 
public:
    List() : _firstPtr(nullptr), _lastPtr(nullptr), _count(0) {}
    ~List();
    void insertAtFront(const double);
    void insertAtBack(const double);
    bool removeFromFront(double&);
    bool removeFromBack(double&);
    bool insertAfterIndex(const size_t idx, const double value);
    size_t getElementCount() const;
    bool isEmpty() const;
    void print() const;
private:
    ListNode* createNode(const double) const;
private:
    ListNode* _firstPtr;
    ListNode* _lastPtr;
    size_t _count;
};

ListNode* List::createNode(const double value) const 
{
    return new ListNode(value);
}

void List::insertAtFront(const double value) 
{
    ListNode* newNode = createNode(value);
    if (isEmpty())
    {
        _firstPtr = _lastPtr = newNode;
    }
    else 
    {
        newNode->_nextPtr = _firstPtr;
        _firstPtr->_prevPtr = newNode; 
        _firstPtr = newNode; 
    }
    _count++;
}

void List::insertAtBack(const double value) 
{
    ListNode* newNode = createNode(value);
    if (isEmpty()) 
    {
        _firstPtr = _lastPtr = newNode;
    }
    else 
    {
        newNode->_prevPtr = _lastPtr; 
        _lastPtr->_nextPtr = newNode; 
        _lastPtr = newNode;
    }
    _count++;
}

bool List::removeFromFront(double& value) 
{
    if (isEmpty()) 
    {
        return false;
    } 
    else 
    {
        ListNode* temp = _firstPtr;
        value = temp->_data;
        if (_firstPtr == _lastPtr)
        {
            _firstPtr = _lastPtr = nullptr;
        }
        else
        {
            _firstPtr = _firstPtr->_nextPtr;
            _firstPtr->_prevPtr = nullptr;
        }
        delete temp;
        _count--;
        return true;
    }
}

bool List::removeFromBack(double& value) 
{
    if (isEmpty()) 
    {
        return false;
    }
    else
    {
        ListNode* temp = _lastPtr;
        value = temp->_data;
        if (_firstPtr == _lastPtr)
        {
            _firstPtr = _lastPtr = nullptr;
        }
        else 
        {
            _lastPtr = _lastPtr->_prevPtr;
            _lastPtr->_nextPtr = nullptr; 
        }
        delete temp;
        _count--;
        return true;
    }
}

bool List::insertAfterIndex(const size_t idx, const double value) 
{                                                                                                             
    if (idx >= _count)
        return false;

    ListNode* newNode = createNode(value);
    ListNode* temp = _firstPtr;
    for (size_t i = 0; i < idx; ++i) 
    {
        temp = temp->_nextPtr;
    }
    newNode->_nextPtr = temp->_nextPtr;
    newNode->_prevPtr = temp;
    if (temp->_nextPtr != nullptr) 
    {
        temp->_nextPtr->_prevPtr = newNode; 
    }
    temp->_nextPtr = newNode; 
    _count++;
    return true;
}

size_t List::getElementCount() const 
{
    return _count;
}

bool List::isEmpty() const 
{
    return _firstPtr == nullptr;
}

void List::print() const 
{
    if (isEmpty()) 
    {
        cout << "List is empty." << endl;
    }
    else 
    {
        ListNode* currentPtr = _firstPtr;
        cout << "The list is: ";
        while (currentPtr != nullptr) 
        {
            cout << currentPtr->_data << " ";
            currentPtr = currentPtr->_nextPtr;
        }
        cout << endl;
    }
}

List::~List() 
{
    while (!isEmpty()) 
    {
        double value;
        removeFromFront(value);
    }
}
