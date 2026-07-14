#pragma once
#include "Includes.h"

namespace Ex {
    inline std::string ReadFileToString(const std::wstring& path) {
        std::ifstream file(path);
        if (!file.is_open()) return "";
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}
