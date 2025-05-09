/*
The Facade pattern provides a unified and simplified interface to a set of
interfaces in a subsystem. It defines a higher-level interface that makes
the subsystem easier to use for clients by hiding the complexities of the components.
*/  
#include <iostream>
using namespace std;

class DVDPlayer {
public:
    void on() { cout << "DVD Player is ON\n"; }
    void play() { cout << "DVD Player is playing\n"; }
    void off() { cout << "DVD Player is OFF\n"; }
};

class Projector {
public:
    void on() { cout << "Projector is ON\n"; }
    void wideScreenMode() { cout << "Projector in widescreen mode\n"; }
    void off() { cout << "Projector is OFF\n"; }
};

class Amplifier {
public:
    void on() { cout << "Amplifier is ON\n"; }
    void setDVD(DVDPlayer* dvd) { cout << "Amplifier set to DVD input\n"; }
    void setSurroundSound() { cout << "Amplifier surround sound ON\n"; }
    void off() { cout << "Amplifier is OFF\n"; }
};

class Lights {
public:
    void dim(int level) { cout << "Lights dimmed to " << level << "%\n"; }
    void on() { cout << "Lights are ON\n"; }
};

// Facade
class Home_Theater_Facade {
private:
    DVDPlayer* dvd;
    Projector* projector;
    Amplifier* amp;
    Lights* lights;

public:
    Home_Theater_Facade(DVDPlayer* d, Projector* p, Amplifier* a, Lights* l)
        : dvd(d), projector(p), amp(a), lights(l) {}

    void watchMovie() {
        cout << "Get ready to watch a movie...\n";
        lights->dim(10);
        projector->on();
        projector->wideScreenMode();
        amp->on();
        amp->setDVD(dvd);
        amp->setSurroundSound();
        dvd->on();
        dvd->play();
    }

    void endMovie() {
        cout << "Shutting movie theater down...\n";
        lights->on();
        projector->off();
        amp->off();
        dvd->off();
    }
};

int main() {
    DVDPlayer dvd;
    Projector projector;
    Amplifier amp;
    Lights lights;

    Home_Theater_Facade homeTheater(&dvd, &projector, &amp, &lights);

    homeTheater.watchMovie();
    cout << "\n--- After movie ---\n";
    homeTheater.endMovie();

    return 0;
}
