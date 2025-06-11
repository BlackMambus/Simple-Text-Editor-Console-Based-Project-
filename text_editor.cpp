#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void displayMenu() {
    cout << "\n==== Simple Text Editor ====\n";
    cout << "1. View File\n";
    cout << "2. Edit File\n";
    cout << "3. Save File\n";
    cout << "4. Save As\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

void viewFile(const vector<string>& lines) {
    cout << "\n--- File Content ---\n";
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << i + 1 << ": " << lines[i] << '\n';
    }
    cout << "---------------------\n";
}

void editFile(vector<string>& lines) {
    int lineNumber;
    string newText;

    cout << "Enter line number to edit (0 to add new line at end): ";
    cin >> lineNumber;
    cin.ignore();

    cout << "Enter new text: ";
    getline(cin, newText);

    if (lineNumber == 0) {
        lines.push_back(newText);
    } else if (lineNumber > 0 && lineNumber <= static_cast<int>(lines.size())) {
        lines[lineNumber - 1] = newText;
    } else {
        cout << "Invalid line number.\n";
    }
}

void saveFile(const vector<string>& lines, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Failed to save file.\n";
        return;
    }

    for (const auto& line : lines) {
        outFile << line << '\n';
    }

    outFile.close();
    cout << "File saved as " << filename << endl;
}

vector<string> loadFile(const string& filename) {
    vector<string> lines;
    ifstream inFile(filename);

    if (!inFile) {
        cout << "File not found. Starting with a blank document.\n";
        return lines;
    }

    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();
    return lines;
}

int main() {
    vector<string> fileLines;
    string filename;

    cout << "Enter filename to open: ";
    getline(cin, filename);
    fileLines = loadFile(filename);

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                viewFile(fileLines);
                break;
            case 2:
                editFile(fileLines);
                break;
            case 3:
                saveFile(fileLines, filename);
                break;
            case 4: {
                string newFilename;
                cout << "Enter new filename: ";
                getline(cin, newFilename);
                saveFile(fileLines, newFilename);
                break;
            }
            case 5:
                cout << "Exiting editor.\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}




