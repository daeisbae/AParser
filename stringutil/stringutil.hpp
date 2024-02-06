#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <queue>
#include <string>

// It's a function that works like split() in python.
// Line Starts From 1 (Obviously!)
// Delimits the "\n" keyword to split the next line.
std::string ExtractTextOfLine(std::string text, const int line);

std::string ConvertCharToString(char ch);

std::queue<char> ConvertStringToQueue(std::string text);

class LineOutOfBoundException : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Line number is out of the bound.";
  }
};

#endif