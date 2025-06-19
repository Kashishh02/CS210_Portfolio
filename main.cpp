#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

// This class does all the work: reading the file, counting items,
// printing counts, histograms, and writing a backup file.
class GroceryTracker {
private:
    map<string, int> itemFrequency;  // key = item name, value = count

public:
    // 1) Load all items from the input file into the map
    void LoadItemsFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error: could not open " << filename << endl;
            return;
        }
        string item;
        while (inFile >> item) {
            itemFrequency[item]++;
        }
        inFile.close();
    }

    // 2) Write the map contents out to a backup file
    void WriteBackupFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error: could not write to " << filename << endl;
            return;
        }
        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << "\n";
        }
        outFile.close();
    }

    // 3) Print count for a single item
    void PrintItemFrequency(const string& item) {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            cout << item << ": " << it->second << "\n";
        } else {
            cout << item << " not found.\n";
        }
    }

    // 4) Print all items and their counts
    void PrintAllItems() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << "\n";
        }
    }

    // 5) Print a histogram of stars for each item
    void PrintHistogram() {
        for (const auto& pair : itemFrequency) {
            // align names to 12 chars for neatness
            cout << setw(12) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << "\n";
        }
    }
};

// Shows the menu options
void DisplayMenu() {
    cout << "\n=== Corner Grocer Menu ===\n"
         << "1) Find frequency of a specific item\n"
         << "2) Print frequency of all items\n"
         << "3) Print histogram of items\n"
         << "4) Exit\n"
         << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker;
    const string inputFile   = "CS210_Project_Three_Input_File.txt";
    const string backupFile  = "frequency.dat";

    // Load data and immediately write a backup copy
    tracker.LoadItemsFromFile(inputFile);
    tracker.WriteBackupFile(backupFile);

    int choice = 0;
    string itemName;

    // Loop until user picks 4 to exit
    do {
        DisplayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter item name: ";
                cin >> itemName;
                tracker.PrintItemFrequency(itemName);
                break;
            case 2:
                tracker.PrintAllItems();
                break;
            case 3:
                tracker.PrintHistogram();
                break;
            case 4:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
