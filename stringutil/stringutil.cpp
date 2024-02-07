#include "stringutil.hpp"

std::string ConvertCharToString(char ch) {
  std::string temp;
  temp.push_back(ch);
  return temp;
}

std::queue<char> ConvertStringToQueue(std::string text) {
  std::queue<char> textqueue;

  for (char ch : text) {
    textqueue.push(ch);
  }
  textqueue.push('\0');

  return textqueue;
}