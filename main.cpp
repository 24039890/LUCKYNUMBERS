#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>

using namespace std;

void getUserNumbers(int chosenNumbers[], int count);
bool isWinner(int userNumbers[], int luckyNumbers[], int count);
void generateLuckyNumbers(int luckyNumbers[]);
void displayNumbers(const string &message, int numbers[], int count);

int main() {
    srand(time(0));

    int chosenCount;
    double betAmount;
    double odds[] = {5.5, 1001, 1650, 10000, 450000, 100000000};

    // Get user input
    cout << "How many numbers would you like to bet on? (1-6): ";
    while (!(cin >> chosenCount) || chosenCount < 1 || chosenCount > 6) {
        cout << "Invalid input! Please enter a number between 1 and 6: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int chosenNumbers[chosenCount];
    getUserNumbers(chosenNumbers, chosenCount);

    cout << "Enter your bet amount: $";
    while (!(cin >> betAmount) || betAmount <= 0) {
        cout << "Invalid amount! Please enter a positive number: $";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    double possibleWin = betAmount * odds[chosenCount - 1];

    // Display user bet details
    cout << "\n****************************************\n";
    cout << "Your Bet Details:\n";
    cout << "Numbers Chosen: ";
    for (int i = 0; i < chosenCount; i++)
        cout << chosenNumbers[i] << " ";
    cout << "\nBet Amount: $" << betAmount;
    cout << "\nPossible Win: $" << possibleWin;
    cout << "\n****************************************\n";

    // Generate lucky numbers
    int luckyNumbers[6];
    generateLuckyNumbers(luckyNumbers);

    // Display lucky numbers
    displayNumbers("\nLucky Numbers Drawn:", luckyNumbers, 6);

    // Check if the user won
    if (isWinner(chosenNumbers, luckyNumbers, chosenCount)) {
        cout << "\n🎉 Congratulations! You won $" << possibleWin << " 🎉\n";
    } else {
        cout << "\n😞 Sorry, you lost. Better luck next time! 😞\n";
    }

    return 0;
}

// Function to get user-selected numbers
void getUserNumbers(int chosenNumbers[], int count) {
    set<int> uniqueNumbers;
    cout << "Enter " << count << " unique lucky numbers (1-36):\n";

    for (int i = 0; i < count; i++) {
        int num;
        while (true) {
            cout << "Number " << (i + 1) << ": ";
            if (!(cin >> num) || num < 1 || num > 36) {
                cout << "Invalid number! Enter a number between 1 and 36.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            if (uniqueNumbers.find(num) != uniqueNumbers.end()) {
                cout << "Duplicate number! Enter a different number.\n";
                continue;
            }
            uniqueNumbers.insert(num);
            chosenNumbers[i] = num;
            break;
        }
    }
}

// Function to generate unique lucky numbers
void generateLuckyNumbers(int luckyNumbers[]) {
    set<int> uniqueNumbers;
    for (int i = 0; i < 6; i++) {
        int num;
        do {
            num = rand() % 36 + 1;
        } while (uniqueNumbers.find(num) != uniqueNumbers.end());
        uniqueNumbers.insert(num);
        luckyNumbers[i] = num;
    }
}

// Function to check if user numbers match lucky numbers
bool isWinner(int userNumbers[], int luckyNumbers[], int count) {
    set<int> luckySet(luckyNumbers, luckyNumbers + 6);
    int matchCount = 0;
    for (int i = 0; i < count; i++) {
        if (luckySet.find(userNumbers[i]) != luckySet.end()) {
            matchCount++;
        }
    }
    return matchCount == count;
}

// Function to display numbers in a formatted way
void displayNumbers(const string &message, int numbers[], int count) {
    cout << message << " ";
    for (int i = 0; i < count; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
}

