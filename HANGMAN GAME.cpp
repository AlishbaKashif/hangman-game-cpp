#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// graphics
vector<string> hangmanStages = {
    "  +---+\n" 
    "      |\n" 
    "      |\n"
    "      |\n"
    "     ===",

    "  +---+\n"
    "  O   |\n"
    "      |\n"
    "      |\n"
    "     ===",

    "  +---+\n"
    "  O   |\n"
    "  |   |\n"
    "      |\n"
    "     ===",

    "  +---+\n"
    "  O   |\n"
    " /|   |\n"
    "      |\n"
    "     ===",

    "  +---+\n"
    "  O   |\n"
    " /|\\  |\n"
    "      |\n"
    "     ===",

    "  +---+\n"
    "  O   |\n"
    " /|\\  |\n"
    " /    |\n"
    "     ===",

    "  +---+\n"
    "  O   |\n"
    " /|\\  |\n"
    " / \\  |\n"
    "     ==="
};

//  hints
struct Word {
    string word;
    string hint;
};

vector<Word> words = {
    {"computer", "An electronic device"},
    {"programming", "What developers do"},
    {"hangman", "Classic word guessing game"},
    {"cplusplus", "Programming language"},
    {"keyboard", "Used for typing"},
    {"algorithm", "Step-by-step solution"}
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showMenu() {
    cout << "=============================\n";
    cout << "        HANGMAN GAME\n";
    cout << "=============================\n";
    cout << "1. Play Game\n";
    cout << "2. Instructions\n";
    cout << "3. Exit\n";
    cout << "Choose an option: ";
}

void instructions() {
    clearScreen();
    cout << "========= INSTRUCTIONS =========\n";
    cout << "- Guess the hidden word one letter at a time\n";
    cout << "- Each wrong guess adds a body part\n";
    cout << "- You lose if the man is fully drawn\n";
    cout << "- You have 2 hints per game\n";
    cout << "- Hint reveals one hidden letter\n";
    cout << "================================\n";
    cout << "Press Enter to return...";
    cin.ignore();
    cin.get();
}

void playGame() {
    clearScreen();
    srand(time(0));

    Word chosen = words[rand() % words.size()];
    string secretWord = chosen.word;
    string hintText = chosen.hint;

    string guessed(secretWord.length(), '_');
    vector<char> usedLetters;

    int wrongGuesses = 0;
    int maxWrong = hangmanStages.size() - 1;
    int hintsLeft = 4;

    while (wrongGuesses < maxWrong && guessed != secretWord) {
        clearScreen();
        cout << hangmanStages[wrongGuesses] << endl;

        cout << "\nWord: ";
        for (char c : guessed) cout << c << " ";

        cout << "\n\nUsed letters: ";
        for (char c : usedLetters) cout << c << " ";

        cout << "\n\nHints left: " << hintsLeft;
        cout << "\nHint: " << hintText;

        cout << "\n\nEnter a letter (or ! for hint): ";
        char guess;
        cin >> guess;
        guess = tolower(guess);

        // Hint request
        if (guess == '!') {
            if (hintsLeft > 0) {
                for (int i = 0; i < secretWord.length(); i++) {
                    if (guessed[i] == '_') {
                        guessed[i] = secretWord[i];
                        break;
                    }
                }
                hintsLeft--;
            }
            continue;
        }

        // Already used
        if (find(usedLetters.begin(), usedLetters.end(), guess) != usedLetters.end()) {
            continue;
        }

        usedLetters.push_back(guess);

        bool correct = false;
        for (int i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == guess) {
                guessed[i] = guess;
                correct = true;
            }
        }

        if (!correct) {
            wrongGuesses++;
        }
    }

    clearScreen();
    cout << hangmanStages[wrongGuesses] << endl;

    if (guessed == secretWord) {
        cout << "\n YOU WON! \n";
    } else {
        cout << "\n YOU LOST!\n";
        cout << "The word was: " << secretWord << endl;
    }

    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}

int main() {
    int choice;

    do {
        clearScreen();
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            playGame();
            break;
        case 2:
            instructions();
            break;
        case 3:
            cout << "Thanks for playing!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
