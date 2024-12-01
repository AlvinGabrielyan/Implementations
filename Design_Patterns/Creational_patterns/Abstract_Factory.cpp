#include <iostream>
#include <memory>

using namespace std;
class Button {
public:
    virtual void render() const = 0;
    virtual ~Button() = default;
};

class WindowsButton : public Button {
public:
    void render() const override {
        cout << "Rendering Windows Button\n";
    }
};

class MacButton : public Button {
public:
    void render() const override {
        cout << "Rendering Mac Button\n";
    }
};

class Checkbox {
public:
    virtual void render() const = 0;
    virtual ~Checkbox() = default;
};

class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        cout << "Rendering Windows Checkbox\n";
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() const override {
        cout << "Rendering Mac Checkbox\n";
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual unique_ptr<Button> createButton() const = 0;// Pure virtual function
    virtual ~GUIFactory() = default;
};

class WindowsFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() const override {
        return make_unique<WindowsButton>();
    }
    unique_ptr<Checkbox> createCheckbox() const override {
        return make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() const override {
        return make_unique<MacButton>();
    }
    unique_ptr<Checkbox> createCheckbox() const override {
        return make_unique<MacCheckbox>();
    }
};

class Application {
private:
    unique_ptr<GUIFactory> factory;

public:
    Application(unique_ptr<GUIFactory> f) : factory(move(f)) {}

    void renderUI() {
        auto button = factory->createButton();
        auto checkbox = factory->createCheckbox();

        button->render();
        checkbox->render();
    }
};

int main() {
    unique_ptr<GUIFactory> windowsFactory = make_unique<WindowsFactory>();
    Application windowsApp(move(windowsFactory));
    cout << "Windows Application UI:\n";
    windowsApp.renderUI();

    unique_ptr<GUIFactory> macFactory = make_unique<MacFactory>();
    Application macApp(move(macFactory));
    cout << "\nMac Application UI:\n";
    macApp.renderUI();

    return 0;
}

