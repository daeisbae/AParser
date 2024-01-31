#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>

// It's a function that works like split() in python.
// Line Starts From 1 (Obviously!)
// Delimits the "\n" keyword to split the next line.
std::string ExtractTextOfLine(std::string text, const int line);

class LineOutOfBoundException : public std::exception {
public:
    std::string what() {
        return "Line number is out of the bound.";
    }
};

#endif