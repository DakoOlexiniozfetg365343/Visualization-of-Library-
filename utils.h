#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>

const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_BLUE = "\033[34m";
const std::string COLOR_MAGENTA = "\033[35m";
const std::string COLOR_CYAN = "\033[36m";
const std::string COLOR_WHITE = "\033[37m";
const std::string COLOR_RESET = "\033[0m";

namespace utils{
    constexpr char DELIMITER = '|';

    bool validateString(const std::string& text);
    bool validateYear(int year);
    bool isNumber(const std::string& str);
    bool validatePhone(const std::string& phone);
    std::string currentDate();
    void printTableHeaders(const std::vector<std::string>& headers);
    void printError(const std::string& message);
    void printSuccess(const std::string& message);
    int inputOptionalInt(const std::string& prompt, int currentValue);
    void backupFile(const std::string& fileName);
    int inputInt(const std::string& prompt);
    std::vector<std::string> split(const std::string& text, char delimiter);
}

#endif
