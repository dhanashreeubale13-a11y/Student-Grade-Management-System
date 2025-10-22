#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to display the word with spaces between letters
void displayWord(const string &word) {
    for (char c : word) {
        cout << c << ' ';
    }
    cout << endl;
}

int main() {
    srand(time(0)); // seed for random

    char playAgain;

    do {
        int maxAttempts = 6;
        int wrongGuesses = 0;

        vector<string> words = {
    "apple", "orange", "mango", "banana", "grape", "lemon",
    "strawberry", "pineapple", "cherry", "peach", "kiwi",
    "watermelon", "papaya", "blueberry", "blackberry", "apricot",
    "plum", "guava", "pear", "pomegranate"
};

        int num = rand() % words.size();

        string secret = words[num];
        string hiddenWord(secret.size(), '_');

        cout << "\nThe word has " << secret.size() << " letters.\n";
        displayWord(hiddenWord);

        char guess;

        while (hiddenWord != secret && wrongGuesses < maxAttempts) {
            cout << "\nEnter a letter to guess the word: ";
            cin >> guess;

            bool found = false;
            for (int i = 0; i < secret.size(); i++) {
                if (secret[i] == guess) {
                    hiddenWord[i] = guess;
                    found = true;
                }
            }

            displayWord(hiddenWord);

            if (!found) {
                wrongGuesses++;
                cout << "Wrong guess! Attempts left: " << (maxAttempts - wrongGuesses) << endl;
            }
        }

        if (hiddenWord == secret) {
            cout << "\n?? Congratulations, you guessed the right word!\n";
        } else {
            cout << "\n?? Sorry, you lose the game. The word was: " << secret << endl;
        }

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);

    } while (playAgain == 'y');

    cout << "\nThanks for playing! Goodbye ??\n";
    return 0;
}
