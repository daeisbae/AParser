/**
 * @file stringutil.hpp
 * @brief Contains the string utility functions
 */
#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <queue>
#include <string>

/**
 * @brief Convert a char to a string
 * @param ch The char to convert
 * @return The string representation of the char
 */
std::string ConvertCharToString(char ch);

/**
 * @brief Convert a string to a queue of chars
 * @param text The string to convert
 * @return The queue representation of the string
 */
std::queue<char> ConvertStringToQueue(std::string text);

#endif
