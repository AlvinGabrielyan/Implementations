// Interface Segregation Principle 
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Printer interface
class Printer {
public:
    virtual void print() const = 0;
    virtual ~Printer() {}
};

// Scanner interface
class Scanner {
public:
    virtual void scan() const = 0;
    virtual ~Scanner() {}
};

// Photocopier interface
class Photocopier {
public:
    virtual void copy() const = 0;
    virtual ~Photocopier() {}
};

// Fax machine interface
class FaxMachine {
public:
    virtual void sendFax(const string& recipient) const = 0;
    virtual ~FaxMachine() {}
};

// Concrete Printer class
class BasicPrinter : public Printer {
public:
    void print() const override {
        cout << "BasicPrinter: Printing document..." << endl;
    }
};

// Concrete Scanner class
class BasicScanner : public Scanner {
public:
    void scan() const override {
        cout << "BasicScanner: Scanning document..." << endl;
    }
};

// Multi-function device
class MultiFunctionDevice : public Printer, public Scanner, public Photocopier, public FaxMachine {
public:
    void print() const override {
        cout << "MultiFunctionDevice: Printing document..." << endl;
    }
    void scan() const override {
        cout << "MultiFunctionDevice: Scanning document..." << endl;
    }
    void copy() const override {
        cout << "MultiFunctionDevice: Copying document..." << endl;
    }
    void sendFax(const string& recipient) const override {
        cout << "MultiFunctionDevice: Sending fax to " << recipient << "..." << endl;
    }
};

// Specialized Photocopier
class OfficePhotocopier : public Photocopier {
public:
    void copy() const override {
        cout << "OfficePhotocopier: Making a photocopy..." << endl;
    }
};

// DeviceManager to manage multiple devices
class DeviceManager {
private:
    vector<unique_ptr<Printer>> printers;
    vector<unique_ptr<Scanner>> scanners;
    vector<unique_ptr<Photocopier>> photocopiers;
    vector<unique_ptr<FaxMachine>> faxMachines;
public:
    void addPrinter(unique_ptr<Printer> printer) {
        printers.push_back(move(printer));
    }

    void addScanner(unique_ptr<Scanner> scanner) {
        scanners.push_back(move(scanner));
    }

    void addPhotocopier(unique_ptr<Photocopier> photocopier) {
        photocopiers.push_back(move(photocopier));
    }

    void addFaxMachine(unique_ptr<FaxMachine> faxMachine) {
        faxMachines.push_back(move(faxMachine));
    }

    void performAllPrinting() const {
        for (const auto& printer : printers) {
            printer->print();
        }
    }

    void performAllScanning() const {
        for (const auto& scanner : scanners) {
            scanner->scan();
        }
    }

    void performAllCopying() const {
        for (const auto& photocopier : photocopiers) {
            photocopier->copy();
        }
    }

    void sendAllFaxes(const string& recipient) const {
        for (const auto& fax : faxMachines) {
            fax->sendFax(recipient);
        }
    }
};

int main() {
    DeviceManager manager;

    // Adding devices
    manager.addPrinter(make_unique<BasicPrinter>());
    manager.addScanner(make_unique<BasicScanner>());
    manager.addPhotocopier(make_unique<OfficePhotocopier>());
    manager.addPrinter(make_unique<MultiFunctionDevice>());
    manager.addScanner(make_unique<MultiFunctionDevice>());
    manager.addFaxMachine(make_unique<MultiFunctionDevice>());

    // Performing operations
    cout << "Performing printing tasks:\n";
    manager.performAllPrinting();

    cout << "\nPerforming scanning tasks:\n";
    manager.performAllScanning();

    cout << "\nPerforming photocopying tasks:\n";
    manager.performAllCopying();

    cout << "\nSending all faxes:\n";
    manager.sendAllFaxes("Alvina");

    return 0;
}

