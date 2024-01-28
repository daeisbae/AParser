#include <sstream>
#include "stringutil.hpp"

std::string ExtractTextOfLine(std::string text, const int line) {
    const char DELIMITER = '\n';

    std::istringstream ss(text);

    std::string strbuf;
    int i = 1;
    std::string linetext;

    while(getline(ss, linetext, DELIMITER)) {
        if(i != line) {
            i++;
            continue;
        }
        return linetext;
    }

    throw LineOutOfBoundException();
}