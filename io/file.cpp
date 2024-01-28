#include <sstream>
#include "file.hpp"
#include "../stringutil/stringutil.hpp"

File::File(std::string filename) {
    this->filename = filename;
    std::ifstream fs;

    fs.open(this->filename);
    if(!fs.is_open()) {
        throw FileNotOpenedException();
    }

    std::stringstream ss;
    ss << fs.rdbuf();

    fs.close();

    this->filedata = ss.str();
}

File::~File() {

}

std::string File::ReadLine(const int line) const {
    if(filedata.empty()) {
        throw FileNotOpenedException();
    }
    return ExtractTextOfLine(this->filedata, line);
}