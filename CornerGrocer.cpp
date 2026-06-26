#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

// GroceryTracker stores the item counts and handles file processing.
class GroceryTracker {
private:
    // Map stores each grocery item as the key and its frequency as the value.
    map<string, int> itemFrequency;

    // These strings store the input file and backup file names.
    string inputFileName;
    string backupFileName;

public:
    // Constructor sets the file names when the object is created.
    GroceryTracker(string inputFile, string backupFile) {
        inputFileName = inputFile;
        backupFileName = backupFile;
    }

    // Reads each grocery item from the input file and counts how often it appears.
    void LoadData() {
        ifstream inputFile(inputFileName);
        string itemName;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open " << inputFileName << endl;
            return;
        }

        while (inputFile >> itemName) {
            itemFrequency[itemName]++;
        }

        inputFile.close();
    }

    // Creates the frequency.dat backup file with each item and its count.
    void CreateBackupFile() {
        ofstream outputFile(backupFileName);

        if (!outputFile.is_open()) {
            cout << "Error: Could not create " << backupFileName << endl;
            return;
        }

        for (const auto& item : itemFrequency) {
            outputFile << item.first << " " << item.second << endl;
        }

        outputFile.close();
    }

    // Returns the frequency for one item entered by the user.
    int GetItemFrequency(string itemName) {
        if (itemFrequency.count(itemName) == 0) {
            return 0;
        }

        return itemFrequency[itemName];
    }

    // Prints every grocery item with its numeric frequency.
    void PrintAllFrequencies() {
        for (const auto& item : itemFrequency) {
            cout << item.first << " " << item.second << endl;
        }
    }

    // Prints every grocery item with a text based histogram.
    void PrintHistogram() {
        for (const auto& item : itemFrequency) {
            cout << item.first << " ";

            for (int i = 0; i < item.second; ++i) {
                cout << "*";
            }

            cout << endl;
        }
    }
};

// Displays the main menu choices for the user.
void PrintMenu() {
    cout << endl;
    cout << "Corner Grocer Item Tracker" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display item frequency histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

// Gets the menu choice and makes sure the user enters a valid number.
int GetMenuChoice() {
    int choice;

    while (true) {
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 4: ";
        }
        else if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Please enter a number from 1 to 4: ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

int main() {
    // Creates the tracker object using the required input and output file names.
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");

    // Loads the grocery data and creates the backup file at the start of the program.
    tracker.LoadData();
    tracker.CreateBackupFile();

    int menuChoice = 0;
    string itemName;

    // Keeps showing the menu until the user chooses option 4.
    while (menuChoice != 4) {
        PrintMenu();
        menuChoice = GetMenuChoice();

        if (menuChoice == 1) {
            cout << "Enter the item name to search for: ";
            cin >> itemName;

            cout << itemName << " appears "
                << tracker.GetItemFrequency(itemName)
                << " times." << endl;
        }
        else if (menuChoice == 2) {
            cout << endl;
            cout << "Item Frequencies" << endl;
            tracker.PrintAllFrequencies();
        }
        else if (menuChoice == 3) {
            cout << endl;
            cout << "Item Frequency Histogram" << endl;
            tracker.PrintHistogram();
        }
        else if (menuChoice == 4) {
            cout << "Exiting program." << endl;
        }
    }

    return 0;
}