#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <memory>
#include <string>

class File {
 private:
  std::string filename;
  std::string filedata;

 public:
  File(std::string filename);
  ~File();

  std::string Read() const;
};

class FileNotOpenedException : public std::exception {
 public:
  const char* what() const noexcept override { return "File Not Opened"; }
};

typedef std::shared_ptr<File> FilePtr;

#endif