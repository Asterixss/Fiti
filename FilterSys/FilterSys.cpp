#include "Includes.h"
#include "Helpers.h"

int main() {
    std::wstring path = L"";
    int choice = 0;

    std::string banner = R"(
   _____ _ _ _   _ 
 |  ___(_) | |_(_)
 | |_  | | | __| |
 |  _| | | | |_| |
 |_|   |_|_|\__|_|
)";

    std::cout << banner << "FITI-1 by yummyzzzz\n";
    std::cout << "\nPlease choose an File\n";
    while (true) {
        if (path.empty()) {
            path = Ex::OpenFileDialog({ {L"Text Files", L"*.txt;*.json;*.csv"} });
            if (path.empty()) {
                std::cout << "[-] No file selected. Try again? (1 Yes | 2 No): ";
                std::cin >> choice;
                if (choice == 1) continue;
                else break;
            }
        }

        std::string fileContent = Ex::ReadFileToString(path);
        std::string searchKey;

        std::cout << "\n[!] Current file: " << std::string(path.begin(), path.end()) << "\n";
        std::cout << "Enter keyword (or type 'NEW' to change file, 'EXIT' to quit): ";
        std::cin >> searchKey;

        if (searchKey == "NEW") { path = L""; continue; }
        if (searchKey == "EXIT") break;

        system("cls");
        std::cout << "-- Results for: " << searchKey << " --\n\n";

        Ex::DisplayFiltered(fileContent, searchKey);

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
    }
    return 0;
}