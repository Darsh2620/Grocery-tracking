#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    // Load items from input file and count frequencies
    void LoadDataFromFile(const string& inputFileName) {
        ifstream inputFile(inputFileName);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open input file." << endl;
            return;
        }

        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();
    }

    // Create backup file frequency.dat
    void CreateBackupFile(const string& backupFileName) {
        ofstream outFile(backupFileName);

        if (!outFile.is_open()) {
            cout << "Error: Could not create backup file." << endl;
            return;
        }

        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }

    // Return frequency of one item
    int GetItemFrequency(const string& itemName) const {
        auto it = itemFrequency.find(itemName);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0;
    }

    // Print all items and numeric frequencies
    void PrintAllFrequencies() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Print histogram
    void PrintHistogram() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Display menu
void PrintMenu() {
    cout << "\n===== Corner Grocer Menu =====" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    GroceryTracker tracker;
    string inputFileName = "Input_File.txt";
    string backupFileName = "frequency.dat";

    tracker.LoadDataFromFile(inputFileName);
    tracker.CreateBackupFile(backupFileName);

    int choice = 0;

    do {
        PrintMenu();

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                string itemName;
                cout << "Enter item name: ";
                cin >> itemName;
                cout << itemName << " appears "
                     << tracker.GetItemFrequency(itemName)
                     << " time(s)." << endl;
                break;
            }
            case 2:
                cout << "\nItem Frequencies:" << endl;
                tracker.PrintAllFrequencies();
                break;
            case 3:
                cout << "\nHistogram:" << endl;
                tracker.PrintHistogram();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid option. Please choose 1, 2, 3, or 4." << endl;
        }

    } while (choice != 4);

    return 0;
}