#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>

#define GREEN_TEXT "\033[1;32m"
#define RED_TEXT "\033[1;31m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"

using namespace std;

/*

This class represents a player in the game, storing their name,
total score, and progress in different game categories (word, logic, and math).
It allows players to earn points, level up in different games, and save or load their progress from a file.

*/

class Player {
private:
    string name;
    int totalScore;
    int wordGameLevel;
    int logicGameLevel;
    int mathGameLevel;

public:
    Player(const string& playerName)
        : name(playerName), totalScore(0),
        wordGameLevel(1), logicGameLevel(1), mathGameLevel(1) {}

    void addPoints(int points) { totalScore += points; }
    int getScore() const { return totalScore; }
    string getName() const { return name; }

    void increaseWordLevel() { wordGameLevel++; }
    void increaseLogicLevel() { logicGameLevel++; }
    void increaseMathLevel() { mathGameLevel++; }

    int getWordLevel() const { return wordGameLevel; }
    int getLogicLevel() const { return logicGameLevel; }
    int getMathLevel() const { return mathGameLevel; }

    bool saveProgress(const string& filename) {
        ofstream file(filename);
        if (!file) return false;

        file << name << endl;
        file << totalScore << endl;
        file << wordGameLevel << endl;
        file << logicGameLevel << endl;
        file << mathGameLevel << endl;

        return true;
    }

    bool loadProgress(const string& filename) {
        ifstream file(filename);
        if (!file) return false;

        getline(file, name);
        file >> totalScore;
        file >> wordGameLevel;
        file >> logicGameLevel;
        file >> mathGameLevel;

        return true;
    }
};

/*

This is an abstract base class for different game types,
defining common attributes like game name and difficulty level.
It provides a structure for game implementation, requiring derived classes to implement the play() and showInstructions() methods.

*/

class Game {
protected:
    int difficulty;
    string gameName;

public:
    Game(const string& name, int diff) : gameName(name), difficulty(diff) {}
    virtual ~Game() {}

    virtual void play(Player& player) = 0;
    virtual void showInstructions() const = 0;

    string getName() const { return gameName; }
    int getDifficulty() const { return difficulty; }
    void setDifficulty(int diff) { difficulty = diff; }
};

/*

The WordGame class challenges players with word-related puzzles, including Hangman and Word Scramble.
It maintains a list of words and their definitions, which change based on the player's level.
The game mechanics involve guessing letters in Hangman and unscrambling words in Word Scramble, rewarding players with points for correct answers.

*/

class WordGame : public Game {
private:
    vector<string> wordList;
    vector<string> definitions;

    void loadWordList(int level) {

        if (level == 1) {
            wordList = { "apple", "banana", "cherry", "orange", "grape",
                         "strawberry", "mango", "pineapple", "watermelon", "peach",
                         "pear", "blueberry", "lemon", "kiwi", "coconut"
            };

            definitions = {
                         "A round fruit with red or green skin and white flesh",
                         "A long curved fruit with yellow skin",
                         "A small round fruit with a stone inside",
                         "A round juicy citrus fruit with orange skin",
                         "A small juicy fruit growing in clusters",
                         "A small red fruit with tiny seeds on its surface",
                         "A tropical fruit with orange flesh and a large pit",
                         "A tropical fruit with spiky skin and sweet yellow flesh",
                         "A large green fruit with a red juicy inside and black seeds",
                         "A soft fruit with a fuzzy skin and a large stone inside",
                         "A green or yellow fruit with a sweet taste and a narrow top",
                         "A small blue fruit that grows in clusters",
                         "A yellow citrus fruit with a sour taste",
                         "A small brown fruit with green flesh and tiny black seeds",
                         "A tropical fruit with a hard shell and white inside" };
        }
        else if (level == 2) {
            wordList = {
                        "elephant", "giraffe", "hippopotamus", "kangaroo", "zebra",
                        "tiger", "lion", "cheetah", "rhinoceros", "panda",
                        "gorilla", "wolf", "fox", "crocodile", "eagle" };

            definitions = {
                        "A large grey mammal with a trunk",
                        "A tall African mammal with a very long neck",
                        "A large African mammal that spends most of its time in water",
                        "An Australian mammal that carries its young in a pouch",
                        "An African wild horse with black and white stripes",
                        "A large orange cat with black stripes",
                        "A large wild cat known as the 'king of the jungle'",
                        "A fast-running wild cat, the fastest land animal",
                        "A large mammal with a horn on its nose",
                        "A black and white bear that eats bamboo",
                        "A large, strong primate that lives in the jungle",
                        "A wild dog-like animal that lives and hunts in packs",
                        "A small wild animal with a bushy tail and a clever nature",
                        "A large reptile with sharp teeth that lives in water",
                        "A large bird of prey with sharp vision and powerful wings" };

        }
        else {
            wordList = {
                        "photosynthesis", "biodiversity", "ecosystem", "metabolism", "adaptation",
                        "evolution", "genetics", "mutation", "cellular", "biotechnology",
                        "gravity", "velocity", "thermodynamics", "osmosis", "neuron" };

            definitions = {
                        "Process by which plants use sunlight to make food",
                        "Variety of plant and animal life in a particular habitat",
                        "A biological community of interacting organisms",
                        "Chemical processes in organisms to maintain life",
                        "The process of change to better suit an environment",
                        "The gradual development of species over time",
                        "The study of heredity and how traits are passed down",
                        "A change in DNA that can affect an organism's traits",
                        "Relating to the smallest unit of life, the cell",
                        "Technology that uses biological systems for innovation",
                        "The force that pulls objects toward Earth",
                        "The speed of an object in a particular direction",
                        "The study of heat and energy transfer",
                        "Movement of water molecules through a membrane",
                        "A specialized cell that transmits nerve impulses" };

        }
    }

    string scrambleWord(const string& word) {
        string scrambled = word;
        random_device rd;
        mt19937 g(rd());
        shuffle(scrambled.begin(), scrambled.end(), g);
        return scrambled;
    }

    void hangmanGame(Player& player) {
        if (wordList.empty()) {
            cout << RED_TEXT << "No words available for this level!" << RESET_TEXT << endl;
            return;
        }

        int index = rand() % wordList.size();
        string word = wordList[index];
        string hint = definitions[index];

        string guessed(word.length(), '_');
        int attempts = 6;
        vector<char> usedLetters;

        cout << "\n=== HANGMAN GAME ===" << endl;
        cout << "Hint: " << hint << endl;

        while (attempts > 0 && guessed != word) {
            cout << "\nWord: " << guessed << endl;
            cout << "Attempts left: " << attempts << endl;

            cout << "Used letters: ";
            for (char c : usedLetters) {
                cout << c << " ";
            }
            cout << endl;

            char letter;
            cout << "Enter a letter: ";
            cin >> letter;
            letter = tolower(letter);

            if (find(usedLetters.begin(), usedLetters.end(), letter) != usedLetters.end()) {
                cout << RED_TEXT << "You already tried this letter!" << RESET_TEXT << endl;
                continue;
            }

            usedLetters.push_back(letter);

            bool found = false;
            for (size_t i = 0; i < word.length(); i++) {
                if (word[i] == letter) {
                    guessed[i] = letter;
                    found = true;
                }
            }

            if (!found) {
                attempts--;
                cout << RED_TEXT << "Wrong letter!" << RESET_TEXT << endl;
            }
            else {
                cout << GREEN_TEXT << "Good guess!" << RESET_TEXT << endl;
            }
        }

        if (guessed == word) {
            cout << "\n" << GREEN_TEXT << "Congratulations! You guessed the word: " << word << RESET_TEXT << endl;
            int points = 10 * word.length();
            player.addPoints(points);
            cout << GREEN_TEXT << "You earned " << points << " points!" << RESET_TEXT << endl;
        }
        else {
            cout << "\n" << RED_TEXT << "Game over! The word was: " << word << RESET_TEXT << endl;
        }
    }

    void wordScrambleGame(Player& player) {
        if (wordList.empty()) {
            cout << RED_TEXT << "No words available for this level!" << RESET_TEXT << endl;
            return;
        }

        int index = rand() % wordList.size();
        string word = wordList[index];
        string hint = definitions[index];
        string scrambled = scrambleWord(word);

        cout << "\n=== WORD SCRAMBLE GAME ===" << endl;
        cout << "Hint: " << hint << endl;
        cout << "Unscramble this word: " << scrambled << endl;

        int attempts = 3;
        while (attempts > 0) {
            string guess;
            cout << "Your guess (attempts left: " << attempts << "): ";
            cin >> guess;

            if (guess == word) {
                cout << GREEN_TEXT << "Correct! You unscrambled the word!" << RESET_TEXT << endl;
                int points = 5 * word.length();
                player.addPoints(points);
                cout << GREEN_TEXT << "You earned " << points << " points!" << RESET_TEXT << endl;
                return;
            }
            else {
                attempts--;
                cout << RED_TEXT << "Incorrect. Try again!" << RESET_TEXT << endl;
            }
        }

        cout << RED_TEXT << "Game over! The word was: " << word << RESET_TEXT << endl;
    }

public:
    WordGame(int difficulty) : Game("Word Challenge", difficulty) {
        loadWordList(difficulty);
    }

    void play(Player& player) override {
        int choice;
        cout << "\n=== " << gameName << " (Level " << difficulty << ") ===" << endl;
        cout << "1. Play Hangman" << endl;
        cout << "2. Play Word Scramble" << endl;
        cout << "3. Back to Game Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hangmanGame(player);
            break;
        case 2:
            wordScrambleGame(player);
            break;
        case 3:
            return;
        default:
            cout << RED_TEXT << "Invalid choice!" << RESET_TEXT << endl;
        }
    }

    void showInstructions() const override {
        cout << "\n=== " << gameName << " Instructions ===" << endl;
        cout << "Hangman: Guess letters to reveal a hidden word." << endl;
        cout << "Word Scramble: Unscramble the letters to form a word." << endl;
        cout << "Both games give hints in the form of definitions." << endl;
    }
};


/*

The LogicGame class includes puzzles that test players' reasoning and pattern-recognition skills.
It features two main challenges: a pattern game, where players identify the next number in a sequence,
and a sequence game, where they continue a Fibonacci-like series.
Players earn points based on difficulty level when they correctly solve a puzzle.

*/

class LogicGame : public Game {
private:
    template<typename T>
    bool getInputWithTimeout(T& input, int timeoutSeconds) {
        atomic<bool> inputProvided(false);

        auto future = async(launch::async, [&input, &inputProvided]() {
            cin >> input;
            inputProvided = true;
            return true;
            });

        for (int i = 0; i < timeoutSeconds; i++) {
            if (inputProvided) {
                future.wait_for(chrono::seconds(0));
                return true;
            }

            cout << "\rTime remaining: " << (timeoutSeconds - i) << " seconds..." << flush;
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << "\r" << YELLOW_TEXT << "Time's up! Moving to the next question..." << RESET_TEXT << endl;

        cin.clear();
        string dummy;
        getline(cin, dummy);

        return false;
    }

    void patternGame(Player& player) {
        cout << "\n=== PATTERN GAME ===" << endl;
        cout << YELLOW_TEXT << "You have 7 seconds to answer each question!" << RESET_TEXT << endl;

        vector<int> pattern;
        int length = 4 + difficulty * 2;

        int start = rand() % 5 + 1;
        int step = rand() % 3 + 1;

        for (int i = 0; i < length; i++) {
            pattern.push_back(start + i * step);
        }

        cout << "Find the next number in the sequence:" << endl;
        for (int i = 0; i < length - 1; i++) {
            cout << pattern[i] << " ";
        }
        cout << "?" << endl;

        int answer = pattern[length - 1];
        int guess;
        cout << "Your answer: ";

        if (getInputWithTimeout(guess, 7)) {
            if (guess == answer) {
                cout << GREEN_TEXT << "Correct! The next number is " << answer << RESET_TEXT << endl;
                int points = 10 * difficulty;
                player.addPoints(points);
                cout << GREEN_TEXT << "You earned " << points << " points!" << RESET_TEXT << endl;
            }
            else {
                cout << RED_TEXT << "Incorrect. The next number was " << answer << RESET_TEXT << endl;
            }
        }
        else {
            cout << "The correct answer was: " << answer << endl;
        }
    }

    void sequenceGame(Player& player) {
        cout << "\n=== SEQUENCE GAME ===" << endl;
        cout << YELLOW_TEXT << "You have 7 seconds to answer each question!" << RESET_TEXT << endl;

        vector<int> sequence;
        int length = 3 + difficulty * 2;

        sequence.push_back(rand() % 5 + 1);
        sequence.push_back(rand() % 5 + 1);

        for (int i = 2; i < length; i++) {
            sequence.push_back(sequence[i - 1] + sequence[i - 2]);
        }

        cout << "Complete the sequence by finding the next TWO numbers:" << endl;
        for (int i = 0; i < length - 2; i++) {
            cout << sequence[i] << " ";
        }
        cout << "? ?" << endl;

        int answer1 = sequence[length - 2];
        int answer2 = sequence[length - 1];
        int guess1, guess2;
        bool answered = false;

        cout << "First number: ";
        if (getInputWithTimeout(guess1, 7)) {
            cout << "Second number: ";
            if (getInputWithTimeout(guess2, 7)) {
                answered = true;
                if (guess1 == answer1 && guess2 == answer2) {
                    cout << GREEN_TEXT << "Correct! The next numbers are " << answer1 << " and " << answer2 << RESET_TEXT << endl;
                    int points = 15 * difficulty;
                    player.addPoints(points);
                    cout << GREEN_TEXT << "You earned " << points << " points!" << RESET_TEXT << endl;
                }
                else {
                    cout << RED_TEXT << "Incorrect. The next numbers were " << answer1 << " and " << answer2 << RESET_TEXT << endl;
                }
            }
        }

        if (!answered) {
            cout << "The correct answers were: " << answer1 << " and " << answer2 << endl;
        }
    }

public:
    LogicGame(int difficulty) : Game("Logic Puzzles", difficulty) {}

    void play(Player& player) override {
        int choice;
        cout << "\n=== " << gameName << " (Level " << difficulty << ") ===" << endl;
        cout << "1. Play Pattern Game" << endl;
        cout << "2. Play Sequence Game" << endl;
        cout << "3. Back to Game Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            patternGame(player);
            break;
        case 2:
            sequenceGame(player);
            break;
        case 3:
            return;
        default:
            cout << RED_TEXT << "Invalid choice!" << RESET_TEXT << endl;
        }
    }

    void showInstructions() const override {
        cout << "\n=== " << gameName << " Instructions ===" << endl;
        cout << "Pattern Game: Find the next number in a mathematical pattern." << endl;
        cout << "Sequence Game: Find the next two numbers in a sequence." << endl;
        cout << "Think carefully about the mathematical relationships!" << endl;
        cout << YELLOW_TEXT << "Note: You have 7 seconds to answer each question!" << RESET_TEXT << endl;
    }
};


/*

The MathGame class tests players' mathematical skills through arithmetic challenges.
It generates problems based on the player's level, such as addition, subtraction, multiplication, and division.
Players must correctly solve these problems within a limited number of attempts to earn points.
The difficulty increases as the player progresses, introducing more complex calculations.

*/

class MathGame : public Game {
private:
    template<typename T>
    bool getInputWithTimeout(T& input, int timeoutSeconds) {
        atomic<bool> inputProvided(false);

        auto future = async(launch::async, [&input, &inputProvided]() {
            cin >> input;
            inputProvided = true;
            return true;
            });

        for (int i = 0; i < timeoutSeconds; i++) {
            if (inputProvided) {
                future.wait_for(chrono::seconds(0));
                return true;
            }

            cout << "\rTime remaining: " << (timeoutSeconds - i) << " seconds..." << flush;
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << "\r" << YELLOW_TEXT << "Time's up! Moving to the next question..." << RESET_TEXT << endl;

        cin.clear();
        string dummy;
        getline(cin, dummy);

        return false;
    }

    void arithmeticGame(Player& player) {
        cout << "\n=== ARITHMETIC GAME ===" << endl;
        cout << YELLOW_TEXT << "You have 3 seconds to answer each question!" << RESET_TEXT << endl;

        int questions = 5 * difficulty;
        int correct = 0;

        for (int i = 0; i < questions; i++) {
            int num1 = rand() % (10 * difficulty) + 1;
            int num2 = rand() % (10 * difficulty) + 1;

            int operation = rand() % (difficulty < 3 ? 2 : 4);
            char opSymbol;
            int correctAnswer;

            switch (operation) {
            case 0:
                opSymbol = '+';
                correctAnswer = num1 + num2;
                break;
            case 1:
                opSymbol = '-';
                if (num2 > num1) swap(num1, num2);
                correctAnswer = num1 - num2;
                break;
            case 2:
                opSymbol = '*';
                num1 = rand() % (5 * difficulty) + 1;
                num2 = rand() % (5 * difficulty) + 1;
                correctAnswer = num1 * num2;
                break;
            case 3:
                opSymbol = '/';
                num2 = rand() % 10 + 1;
                correctAnswer = rand() % 10 + 1;
                num1 = num2 * correctAnswer;
                break;
            }

            cout << "\nQuestion " << (i + 1) << ": " << num1 << " " << opSymbol << " " << num2 << " = ?" << endl;

            int answer;
            cout << "Your answer: ";

            if (getInputWithTimeout(answer, 3)) {
                if (answer == correctAnswer) {
                    cout << GREEN_TEXT << "Correct!" << RESET_TEXT << endl;
                    correct++;
                }
                else {
                    cout << RED_TEXT << "Wrong! The correct answer is " << correctAnswer << RESET_TEXT << endl;
                }
            }
            else {
                cout << "The correct answer was: " << correctAnswer << endl;
            }
        }

        int points = 5 * correct * difficulty;
        cout << "\nYou got " << correct << " out of " << questions << " correct!" << endl;
        player.addPoints(points);
        cout << GREEN_TEXT << "You earned " << points << " points!" << RESET_TEXT << endl;
    }

    void multiplicationTableGame(Player& player) {
        cout << "\n=== MULTIPLICATION TABLE GAME ===" << endl;
        cout << YELLOW_TEXT << "You have 3 seconds to answer each question!" << RESET_TEXT << endl;

        int questions = 5 * difficulty;
        int correct = 0;
        int maxNumber = 5 + difficulty * 5;

        for (int i = 0; i < questions; i++) {
            int num1 = rand() % maxNumber + 1;
            int num2 = rand() % maxNumber + 1;
            int correctAnswer = num1 * num2;

            cout << "\nQuestion " << (i + 1) << ": " << num1 << " × " << num2 << " = ?" << endl;

            int answer;
            cout << "Your answer: ";

            if (getInputWithTimeout(answer, 3)) {
                if (answer == correctAnswer) {
                    cout << GREEN_TEXT << "Correct!" << RESET_TEXT << endl;
                    correct++;
                }
                else {
                    cout << RED_TEXT << "Wrong! The correct answer is " << correctAnswer << RESET_TEXT << endl;
                }
            }
            else {
                cout << "The correct answer was: " << correctAnswer << endl;
            }
        }

        int points = 5 * correct * difficulty;
        cout << "\nYou got " << correct << " out of " << questions << " correct!" << endl;
        player.addPoints(points);
        cout << GREEN_TEXT << "You earned " << points << " points!" << RESET_TEXT << endl;
    }

public:
    MathGame(int difficulty) : Game("Math Masters", difficulty) {}

    void play(Player& player) override {
        int choice;
        cout << "\n=== " << gameName << " (Level " << difficulty << ") ===" << endl;
        cout << "1. Play Arithmetic Game" << endl;
        cout << "2. Play Multiplication Table Game" << endl;
        cout << "3. Back to Game Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            arithmeticGame(player);
            break;
        case 2:
            multiplicationTableGame(player);
            break;
        case 3:
            return;
        default:
            cout << RED_TEXT << "Invalid choice!" << RESET_TEXT << endl;
        }
    }

    void showInstructions() const override {
        cout << "\n=== " << gameName << " Instructions ===" << endl;
        cout << "Arithmetic Game: Solve various math problems with +, -, *, and /." << endl;
        cout << "Multiplication Table Game: Test your multiplication skills." << endl;
        cout << "Higher difficulty levels include more complex operations!" << endl;
        cout << YELLOW_TEXT << "Note: You have 3 seconds to answer each question!" << RESET_TEXT << endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "====================================" << endl;
    cout << GREEN_TEXT << "     WELCOME TO BRAIN QUEST!        " << RESET_TEXT << endl;
    cout << "====================================" << endl;
    cout << "The educational game that tests your knowledge and skills!" << endl;

    string playerName;
    cout << "\nEnter your name: ";
    getline(cin, playerName);

    Player player(playerName);

    string saveFile = playerName + "_save.txt";
    if (player.loadProgress(saveFile)) {
        cout << GREEN_TEXT << "Welcome back, " << player.getName() << "!" << RESET_TEXT << endl;
        cout << "Your current score: " << player.getScore() << endl;
    }
    else {
        cout << GREEN_TEXT << "Welcome, " << player.getName() << "!" << RESET_TEXT << endl;
    }

    bool running = true;
    while (running) {
        cout << "\n====== MAIN MENU ======" << endl;
        cout << "1. Play Word Game (Level " << player.getWordLevel() << ")" << endl;
        cout << "2. Play Logic Game (Level " << player.getLogicLevel() << ")" << endl;
        cout << "3. Play Math Game (Level " << player.getMathLevel() << ")" << endl;
        cout << "4. View Instructions" << endl;
        cout << "5. View Score" << endl;
        cout << "6. Save Progress" << endl;
        cout << "7. Exit Game" << endl;
        cout << "=======================" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            WordGame wordGame(player.getWordLevel());
            wordGame.play(player);

            if (player.getScore() >= player.getWordLevel() * 100) {
                player.increaseWordLevel();
                cout << "\n" << GREEN_TEXT << "Congratulations! You've advanced to Word Game Level "
                    << player.getWordLevel() << "!" << RESET_TEXT << endl;
            }
            break;
        }
        case 2: {
            LogicGame logicGame(player.getLogicLevel());
            logicGame.play(player);

            if (player.getScore() >= player.getLogicLevel() * 100) {
                player.increaseLogicLevel();
                cout << "\n" << GREEN_TEXT << "Congratulations! You've advanced to Logic Game Level "
                    << player.getLogicLevel() << "!" << RESET_TEXT << endl;
            }
            break;
        }
        case 3: {
            MathGame mathGame(player.getMathLevel());
            mathGame.play(player);

            if (player.getScore() >= player.getMathLevel() * 100) {
                player.increaseMathLevel();
                cout << "\n" << GREEN_TEXT << "Congratulations! You've advanced to Math Game Level "
                    << player.getMathLevel() << "!" << RESET_TEXT << endl;
            }
            break;
        }
        case 4: {
            cout << "\n====== GAME INSTRUCTIONS ======" << endl;
            cout << "Choose which instructions to view:" << endl;
            cout << "1. Word Game" << endl;
            cout << "2. Logic Game" << endl;
            cout << "3. Math Game" << endl;
            cout << "4. Back to Main Menu" << endl;

            int instructionChoice;
            cin >> instructionChoice;

            switch (instructionChoice) {
            case 1: {
                WordGame temp(1);
                temp.showInstructions();
                break;
            }
            case 2: {
                LogicGame temp(1);
                temp.showInstructions();
                break;
            }
            case 3: {
                MathGame temp(1);
                temp.showInstructions();
                break;
            }
            case 4:
                break;
            default:
                cout << RED_TEXT << "Invalid choice!" << RESET_TEXT << endl;
            }
            break;
        }
        case 5:
            cout << "\n====== PLAYER STATS ======" << endl;
            cout << "Player: " << player.getName() << endl;
            cout << "Total Score: " << player.getScore() << endl;
            cout << "Word Game Level: " << player.getWordLevel() << endl;
            cout << "Logic Game Level: " << player.getLogicLevel() << endl;
            cout << "Math Game Level: " << player.getMathLevel() << endl;
            break;
        case 6:
            if (player.saveProgress(saveFile)) {
                cout << GREEN_TEXT << "Progress saved successfully!" << RESET_TEXT << endl;
            }
            else {
                cout << RED_TEXT << "Failed to save progress!" << RESET_TEXT << endl;
            }
            break;
        case 7:
            cout << "\n" << GREEN_TEXT << "Thank you for playing Brain Quest!" << RESET_TEXT << endl;
            cout << "Final Score: " << player.getScore() << endl;
            running = false;
            break;
        default:
            cout << RED_TEXT << "Invalid choice! Please try again." << RESET_TEXT << endl;
        }
    }

    return 0;
}
