// Dependency Inversion Principle 
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// --- Abstractions for Notifications ---
class Notification {
public:
    virtual void send(const string& message) const = 0;
    virtual ~Notification() {}
};

// --- Concrete Notification Implementations ---
class EmailNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "Sending Email: " << message << endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "Sending SMS: " << message << endl;
    }
};

class PushNotification : public Notification {
public:
    void send(const string& message) const override {
        cout << "Sending Push Notification: " << message << endl;
    }
};

// --- User Class ---
class User {
private:
    string name;
    vector<Notification*> notifications;  // User can subscribe to multiple notification types
public:
    User(const string& name) : name(name) {}

    void addNotification(Notification* notification) {
        notifications.push_back(notification);
    }

    void sendNotifications(const string& message) {
        cout << "Notifying " << name << "...\n";
        for (const auto& notification : notifications) {
            notification->send(message);
        }
    }
};

// --- Logger Class (for logging notifications sent) ---
class Logger {
public:
    void log(const string& message) const {
        cout << "Log: " << message << endl;
    }
};

// --- Admin Class for Managing Users and Notifications ---
class Admin {
private:
    Logger logger;
public:
    void createUser(const string& userName, vector<Notification*> notifications) {
        User user(userName);
        for (auto& notif : notifications) {
            user.addNotification(notif);
        }
        user.sendNotifications("Welcome to the Notification System!");
        logger.log(userName + " has been notified.");
    }
};

// --- Main Function ---
int main() {
    // Create notification objects
    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    // Create an admin to manage users
    Admin admin;

    // Create a new user and assign different notifications to them
    vector<Notification*> notifications = {&email, &sms, &push};
    admin.createUser("Alvina", notifications);

    // Another user with only email notifications
    vector<Notification*> emailOnly = {&email};
    admin.createUser("David", emailOnly);

    return 0;
}

