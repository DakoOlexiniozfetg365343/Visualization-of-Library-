#include "utils.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <string>
#include <vector>
#include <ctime>

namespace utils{
    bool validateString(const std::string& text){
      return !text.empty() && std::all_of(text.begin(), text.end(), [](char c) -> bool{
        return std::isalpha(c) || c == ' ' || c == '-' || c == '\'';
      });
    }

    bool validateYear(int year){
      return year >= 1800 && year <= std::time(nullptr) / 31536000 + 1970;
    }
    bool isNumber(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

    bool validatePhone(const std::string& phone){
      std::regex pattern("\\+?\\d{10,12}");
      return std::regex_match(phone, pattern);
    }

    std::string currentDate(){
      std::time_t now = std::time(nullptr);
      char buffer[11];
      std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&now));
      return buffer;
    }

    void printTableHeaders(const std::vector<std::string>& headers){
      for (const auto& header : headers)
          std::cout << std::left << std::setw(20) << header << "|";
      std::cout << "\n" << std::string(headers.size() * 21, '-') << "\n";
    }

    void printError(const std::string& message){
      std::cout << COLOR_RED << "Error: " << message << COLOR_RESET << "\n";
    }

    void printSuccess(const std::string& message){
      std::cout << COLOR_GREEN << "Success: " << message << COLOR_RESET << "\n";
    }

    int inputOptionalInt(const std::string& prompt, int currentValue) {
    std::string input;
    std::cout << prompt << " (leave empty to keep current: " << currentValue << "): ";
    std::getline(std::cin, input);

    if (input.empty()) return currentValue;

    try {
        int val = std::stoi(input);
        return val;
    } catch (...) {
        std::cout << "Invalid number, try again.\n";
        return inputOptionalInt(prompt, currentValue);
    }
    }



    void backupFile(const std::string& fileName){
      std::fstream source(fileName);
      if(!source) return;
      std::ofstream destination("backup_" + fileName + "_" + currentDate() + ".txt");
      destination << source.rdbuf();
      source.close();
      destination.close();
    }
    int inputInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                return value;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "❌ Invalid input. Please enter a number.\n";
            }
        }
    }

    std::vector<std::string> split(const std::string& text, char delimiter){
      std::vector<std::string> result;
      std::string token;
      for(auto c : text){
        if(c == delimiter){
          result.push_back(token);
          token.clear();
        } else {
          token += c;
        }
      }
      if(!token.empty()) result.push_back(token);
      return result;
    }

}