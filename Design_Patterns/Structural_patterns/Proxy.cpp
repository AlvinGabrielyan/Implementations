/* The Proxy design pattern provides a surrogate or placeholder for another object to control access to it.
It acts as an intermediary that forwards requests to the real object only after performing additional functionality 
such as authentication, lazy initialization, or access control. In essence, a proxy represents the real object while adding a layer of 
indirection that lets you perform actions before or after the request reaches the actual object.*/

#include <iostream>
#include <string>

using namespace std;

class BankAccount {
public:
    virtual bool checkPin(int pin) = 0;
    virtual void withdraw(int amount) = 0;
    virtual int getBalance() = 0;
    virtual ~BankAccount() = default;
};

class RealBankAccount : public BankAccount {
private:
    string accountNumber;
    int balance;
    int correctPin;
    
public:
    RealBankAccount(string accountNum, int initialBalance, int pin) : accountNumber(accountNum), balance(initialBalance), correctPin(pin) {
        cout << "Real bank account created" << endl;
    }
    
    bool checkPin(int pin) override {
             return pin == correctPin;
    }
    
    void withdraw(int amount) override {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrew " << amount << " dollars" << endl;
        } else {
            cout << "Insufficient funds" << endl;
        }
    }
    
    int getBalance() override {
        return balance;
    }
};

// ATM apahovuma safety-utyuny, amen functioni vra stuguma vaveracvaca te che nor toxnuma gorcoxutyuny katarvi
class ATMProxy : public BankAccount {
private:
    RealBankAccount* realAccount;
    bool authenticated;
    
public:
    ATMProxy(RealBankAccount* account) 
        : realAccount(account), authenticated(false) {
        cout << "ATM proxy created" << endl;
    }
    
    bool checkPin(int pin) override {
        authenticated = realAccount->checkPin(pin);
        if (authenticated) {
            cout << "PIN correct - access granted" << endl;
        } else {
            cout << "Incorrect PIN - access denied" << endl;
        }
        return authenticated;
    }
    
    void withdraw(int amount) override {
        if (!authenticated) {
            cout << "Please verify your PIN first" << endl;
            return;
        }
        
        realAccount->withdraw(amount);
    }
    
    int getBalance() override {
        if (!authenticated) {
            cout << "Please verify your PIN first" << endl;
            return -1;
        }
        
        return realAccount->getBalance();
    }
};

int main() { 
  //Stex talis enq irakan arjeqnery, heto hamakargy hamematuma sranc het mutqagrvacy
     RealBankAccount* account = new RealBankAccount("123456789", 1000, 1234);

  ATMProxy atm(account);
    
    cout << "\n Before authentication" << endl;
    atm.withdraw(100);
    
    cout << "\n Authentication with wrong PIN " << endl;
    atm.checkPin(5555);
    
    cout << "\n Authentication with correct PIN " << endl;
    atm.checkPin(1234);
    
    cout << "\n After authentication " << endl;
    cout << "Current balance: " << atm.getBalance() << endl;
    atm.withdraw(500);
    cout << "New balance: " << atm.getBalance() << endl;
    
    delete account;
    return 0;
}
