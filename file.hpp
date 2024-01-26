#ifndef FILE_H
#define FILE_H

#include <string>

class File {
private:
    std::string filename;
    std::string filedata;
    int maxline;
    int currline;

public:
    File(std::string filename);
    ~File();

    std::string Filename();
    std::string ReadLine();
    void LoadFile();
};


typedef std::shared_ptr<File> FilePtr;

#endif