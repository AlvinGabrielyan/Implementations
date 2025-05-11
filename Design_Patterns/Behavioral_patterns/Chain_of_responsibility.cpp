/*Chain of Responsibility is a behavioral design pattern that lets you pass requests along a chain of handlers. 
Each handler decides either to process the request or pass it to the next one in the chain.*/
#include <iostream>
#include <string>

using namespace std;

class PurchaseRequest {
public:
    double amount;
    string purpose;

    PurchaseRequest(double amt, const string& purp) : amount(amt), purpose(purp) {}
};

// Abstract handler class
class Approver {
protected:
    Approver* nextApprover;
public:
    Approver() : nextApprover(NULL) {}

    void setNextApprover(Approver* next) {
        nextApprover = next;
    }

    virtual void processRequest(PurchaseRequest request) {
        if (nextApprover != NULL)
            nextApprover->processRequest(request);
    }

    virtual ~Approver() {}
};


class Manager : public Approver {
public:
    void processRequest(PurchaseRequest request) override {
        if (request.amount <= 1000) {
            cout << "Manager approved request: " << request.purpose
                 << " ($" << request.amount << ")\n";
        } else if (nextApprover != NULL) {
            nextApprover->processRequest(request);
        }
    }
};

class Director : public Approver {
public:
    void processRequest(PurchaseRequest request) override {
        if (request.amount <= 5000) {
            cout << "Director approved request: " << request.purpose
                 << " ($" << request.amount << ")\n";
        } else if (nextApprover != NULL) {
            nextApprover->processRequest(request);
        }
    }
};

class CEO : public Approver {
public:
    void processRequest(PurchaseRequest request) override {
        if (request.amount <= 10000) {
            cout << "CEO approved request: " << request.purpose
                 << " ($" << request.amount << ")\n";
        } else {
            cout << "Request requires board approval: " << request.purpose
                 << " ($" << request.amount << ")\n";
        }
    }
};

int main() {
    
    Manager manager;
    Director director;
    CEO ceo;

    //The chain: Manager → Director → CEO
    manager.setNextApprover(&director);
    director.setNextApprover(&ceo);

    PurchaseRequest req1(500, "Office Supplies");
    PurchaseRequest req2(3000, "Team Building Event");
    PurchaseRequest req3(8000, "New Servers");
    PurchaseRequest req4(15000, "R&D Project");

    manager.processRequest(req1);
    manager.processRequest(req2);
    manager.processRequest(req3);
    manager.processRequest(req4);

    return 0;
}
