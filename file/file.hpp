#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <memory>

class File {
private:
    std::string filename;
    std::string filedata;

public:
    File(std::string filename);
    ~File();

    std::string ReadLine(const int line) const;
};

class FileNotOpenedException : public std::exception {
public:
    const char* what() const noexcept override {
        return "File Not Opened";
    }
};

typedef std::shared_ptr<File> FilePtr;

#endif