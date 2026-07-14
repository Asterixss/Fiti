#pragma once
#include "Includes.h"

namespace Ex {
    void DisplayFiltered(const std::string& content, const std::string& filter) {
        std::vector<std::string> lines;
        std::stringstream ss(content);
        std::string line;
        while (std::getline(ss, line)) lines.push_back(line);

        std::vector<int> foundIndices;
        for (int i = 0; i < lines.size(); ++i) {
            if (lines[i].find(filter) != std::string::npos) {
                foundIndices.push_back(i);
            }
        }

        if (foundIndices.empty()) {
            std::cout << "[-] Nothing found for: " << filter << "\n\n";
            return;
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        std::vector<bool> printed(lines.size(), false);

        for (int idx : foundIndices) {
            int start = std::max(0, idx - 5);
            int end = std::min((int)lines.size() - 1, idx + 5);

            for (int i = start; i <= end; ++i) {
                if (printed[i]) continue;
                printed[i] = true;

                std::cout << i + 1 << ": ";
                if (i == idx) {
                    // Highlight the keyword
                    size_t pos = 0;
                    std::string temp = lines[i];
                    while ((pos = temp.find(filter)) != std::string::npos) {
                        std::cout << temp.substr(0, pos);
                        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                        std::cout << filter;
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        temp.erase(0, pos + filter.length());
                    }
                    std::cout << temp << "\n";
                }
                else {
                    std::cout << lines[i] << "\n";
                }
            }
            std::cout << "------------------------------------------\n";
        }
    }
}