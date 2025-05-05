/*
The purpose of this is that we can set whichever values we want using just the dot (.) operator — we’re essentially performing a cascade-style call.
Otherwise, we’d have to set each variable in the constructor every time,
and each time we’d have to recheck the order to avoid messing it up, etc.
With this approach, we just set whatever we need (e.g., this.setRam().setHdd().setSSD() etc.).

Finally, whatever we set in our builder gets passed into the appropriate constructor
(the Computer class is nested here).
*/

//Սրա նպատակն էնա, որ ամեն անգամ ինչն ուզենք էդ էլ set անենք, ուղղակի ․ դնելով, մոտավոր կասկադային կանչ ենք իրականացնում,
հակառակ դեպքում կոնստրուկտորում պետք է ամեն անգամ սեթ անեինք հերթով փոփոխականները,
ու ամեն անգամ պետք ա վերանայենք, հերթականությունը չխախտենք և այլն, ստեղ որն ուզում ենք, էդ ենք սեթ անում։(this.setRam.setHdd.setSSD.և այլն)
Վերջում էլ ինչ դրել ենք մեր builder մեջ, բերում դնում ենք համապատասխան կանստրուկտորի մեջ(computer-ը nested ա)
   /* this.HDD=builder.HDD;
		this.RAM=builder.RAM;
		this.isGraphicsCardEnabled=builder.isGraphicsCardEnabled;
		this.isBluetoothEnabled=builder.isBluetoothEnabled;*/

#include <iostream>
#include <string>

using namespace std;

class Computer {
public:

    string getHDD() const { return HDD; }
    string getRAM() const { return RAM; }
    bool isGraphicsCardEnabled() const { return graphicsCardEnabled; }
    bool isBluetoothEnabled() const { return bluetoothEnabled; }

    // Nested Builder class
    class ComputerBuilder {
    private:
    
        string HDD;
        string RAM;

        bool graphicsCardEnabled = false;
        bool bluetoothEnabled = false;

    public:
    
        ComputerBuilder(const string& hdd, const string& ram)
            : HDD(hdd), RAM(ram) {}

        ComputerBuilder& setGraphicsCardEnabled(bool enabled) {
            graphicsCardEnabled = enabled;
            return *this; 
        }

             ComputerBuilder& setBluetoothEnabled(bool enabled) {
            bluetoothEnabled = enabled;
            return *this;
        }

        Computer build() const {
            return Computer(*this);
        }

        friend class Computer;
    };

private:

    string HDD;
    string RAM;

    bool graphicsCardEnabled;
    bool bluetoothEnabled;

    Computer(const ComputerBuilder& builder)
        : HDD(builder.HDD),
          RAM(builder.RAM),
          graphicsCardEnabled(builder.graphicsCardEnabled),
          bluetoothEnabled(builder.bluetoothEnabled) {}

public:

    void displayConfiguration() const {
        cout << "HDD: " << HDD << "\n";
        cout << "RAM: " << RAM << "\n";
        cout << "Graphics Card Enabled: " << (graphicsCardEnabled ? "Yes" : "No") << "\n";
        cout << "Bluetooth Enabled: " << (bluetoothEnabled ? "Yes" : "No") << "\n";
    }
};

int main() {
    
    Computer myComputer = Computer::ComputerBuilder("1TB", "16GB")
                              .setGraphicsCardEnabled(true)
                              .setBluetoothEnabled(true)
                              .build();

    myComputer.displayConfiguration();

    return 0;
}
