#include "stringutil.hpp"

#include <sstream>

std::string ExtractTextOfLine(std::string text, const int line) {
  const char DELIMITER = '\n';

  std::istringstream ss(text);

  std::string strbuf;
  int i = 1;
  std::string linetext;

  while (getline(ss, linetext, DELIMITER)) {
    if (i != line) {
      i++;
      continue;
    }
    return linetext;
  }

  throw LineOutOfBoundException();
}

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