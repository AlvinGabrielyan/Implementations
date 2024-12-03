
#include <iostream>
#include <string>
using namespace std;

class PaymentStrategy {
public:
    virtual void pay(int amount) const = 0;
    virtual ~PaymentStrategy() {}
};

class CreditCardPayment : public PaymentStrategy {
private:
    string name;
    string cardNumber;
    string cvv;

public:
    CreditCardPayment(const string& name, const string& cardNumber, const string& cvv)
        : name(name), cardNumber(cardNumber), cvv(cvv) {}

    void pay(int amount) const override {
        cout << "Paid " << amount << " using Credit Card (Name: " << name << ")." << endl;
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    string email;

public:
    PayPalPayment(const string& email) : email(email) {}

    void pay(int amount) const override {
        cout << "Paid " << amount << " using PayPal (Email: " << email << ")." << endl;
    }
};

class PaymentProcessor {
private:
    PaymentStrategy* strategy; 

public:
    PaymentProcessor(PaymentStrategy* strategy) : strategy(strategy) {}

    void setStrategy(PaymentStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void processPayment(int amount) const {
        if (strategy) {
            strategy->pay(amount);
        } else {
            cout << "No payment strategy selected!" << endl;
        }
    }
};

int main() {
    CreditCardPayment creditCard("Alice", "1234-5678-9876-5432", "123");
    PayPalPayment paypal("alice@example.com");

    PaymentProcessor processor(&creditCard);

    cout << "Processing with Credit Card:" << endl;
    processor.processPayment(100);

    cout << "\nSwitching to PayPal:" << endl;
    processor.setStrategy(&paypal);
    processor.processPayment(200);

    return 0;
}
