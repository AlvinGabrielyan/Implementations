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

class MultiFunctionDevice : public Printer, public Scanner {
public:
    void print() const override {
        cout << "MultiFunctionDevice: Printing document..." << endl;
    }
    void scan() const override {
        cout << "MultiFunctionDevice: Scanning document..." << endl;
    }
};

class DeviceManager {
private:
    vector<unique_ptr<Printer>> printers;
    vector<unique_ptr<Scanner>> scanners;
public:
    void addPrinter(unique_ptr<Printer> printer) {
        printers.push_back(move(printer));
    }

    void addScanner(unique_ptr<Scanner> scanner) {
        scanners.push_back(move(scanner));
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
};

int main() {
    DeviceManager manager;

    manager.addPrinter(make_unique<BasicPrinter>());
    manager.addScanner(make_unique<BasicScanner>());
    manager.addPrinter(make_unique<MultiFunctionDevice>());
    manager.addScanner(make_unique<MultiFunctionDevice>());

    cout << "Performing printing tasks:\n";
    manager.performAllPrinting();

    cout << "\nPerforming scanning tasks:\n";
    manager.performAllScanning();

    return 0;
}
