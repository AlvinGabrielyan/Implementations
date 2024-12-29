#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Notification {
public:
    virtual void send(const string& message) const = 0;
    virtual ~Notification() {}
};

class EmailNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "Email: " << message << endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "SMS: " << message << endl;
    }
};
//Mer user class-y enpes enq sarqum, vor kaxvac lini base class-ic,
//voch te derived-neric aysinqn abstraction-ic a kaxvac voch te implementation-ic
class User {
private:
    vector<Notification*> notifications;
public:
    void addNotification(Notification* notification) {
        notifications.push_back(notification);
    }

    void notify(const string& message) const {
        for (const auto& n : notifications) n->send(message);
    }
};

int main() {
    EmailNotification email;
    SMSNotification sms;

    User user;
    user.addNotification(&email);
    user.addNotification(&sms);
    user.notify("Hello, Dependency Inversion!");

    return 0;
}
