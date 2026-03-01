#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

/*
 * Class: ItemTracker
 * Purpose: Tracks item purchase frequencies from input file
 */
class ItemTracker {
private:
    map<string, int> itemFrequency;  // Stores item and count
    string inputFileName = "CS210_Project_Three_Input_File.txt";
    string backupFileName = "frequency.dat";

public:

    // Constructor: Loads file and builds frequency map
    ItemTracker() {
        loadFileData();
        createBackupFile();
    }

    /*
     * Function: loadFileData
     * Purpose: Reads input file and populates map
     */
    void loadFileData() {
        ifstream inputFile(inputFileName);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Unable to open input file." << endl;
            return;
        }

        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();
    }

    /*
     * Function: createBackupFile
     * Purpose: Writes frequency data to frequency.dat
     */
    void createBackupFile() {
        ofstream outputFile(backupFileName);

        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
    }

    /*
     * Function: getItemFrequency
     * Purpose: Returns frequency of user-input item
     */
    void getItemFrequency() {
        string searchItem;
        cout << "Enter item name: ";
        cin >> searchItem;

        if (itemFrequency.count(searchItem) > 0) {
            cout << searchItem << " was purchased "
                 << itemFrequency[searchItem] << " time(s)." << endl;
        }
        else {
            cout << searchItem << " was not found." << endl;
        }
    }

    /*
     * Function: printAllFrequencies
     * Purpose: Displays all items and counts
     */
    void printAllFrequencies() {
        cout << "\nItem Purchase Frequencies:\n";
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first
                 << pair.second << endl;
        }
    }

    /*
     * Function: printHistogram
     * Purpose: Displays frequency as asterisks
     */
    void printHistogram() {
        cout << "\nItem Purchase Histogram:\n";
        for (const auto& pair : itemFrequency) {
            cout << setw(15) << left << pair.first;
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

/*
 * Function: displayMenu
 * Purpose: Shows user options
 */
void displayMenu() {
    cout << "\n===== Corner Grocer Menu =====\n";
    cout << "1. Search for item frequency\n";
    cout << "2. Print all item frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";
}

/*
 * Main Function
 */
int main() {
    ItemTracker tracker;
    int choice = 0;

    // Menu loop
    while (choice != 4) {
        displayMenu();
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            tracker.getItemFrequency();
            break;
        case 2:
            tracker.printAllFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please select 1-4." << endl;
        }
    }

    return 0;
}