#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // For std::find

using namespace std;

class Observer {
public:
    virtual void update(const string& message) = 0;
};

class Subject {
public:
    virtual void subscribe(Observer* observer) = 0;
    virtual void unsubscribe(Observer* observer) = 0;
    virtual void notify() = 0;
};

class GroupChat : public Subject {
public:
    vector<Observer*> observers;
    string latestMessage;

    void subscribe(Observer* observer) override {
        observers.push_back(observer);
    }

    void unsubscribe(Observer* observer) override {
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {  // Check if observer was found
            observers.erase(it);
        }
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(latestMessage);
        }
    }

    void sendMessage(const string& message) {
        latestMessage = message;
        notify();
    }
};

class Friend : public Observer {
public:
    string name;

    Friend(const string& n) : name(n) {}

    void update(const string& message) override {
        cout << name << " received: " << message << endl;
    }
};

int main() {
    GroupChat chat;

    Friend friend1("Anna");
    Friend friend2("Bob");

    chat.subscribe(&friend1);
    chat.subscribe(&friend2);

    chat.sendMessage("Hi everyone");

    chat.unsubscribe(&friend2);
    chat.sendMessage("Hi everyone");

    return 0;
}
