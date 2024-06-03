#include "file.hpp"

#include <sstream>

#include "stringutil.hpp"

File::File(std::string filename) {
  filename_ = filename;
  std::ifstream fs;

  fs.open(filename_);
  if (!fs.is_open()) {
    throw FileNotOpenedException();
  }

  std::stringstream ss;
  ss << fs.rdbuf();

  fs.close();

    filename_ = ss.str();
}

File::~File() {}

std::string File::Read() const {
  if (file_data_.empty()) throw FileNotOpenedException();
  return file_data_;
}