/**
 * @file file.hpp
 * @brief Contains the Script read operations and related exceptions
 */
#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <memory>
#include <string>

/**
 * @brief File class to read the script file
 */
class File {
 private:
  std::string filename_;
  std::string file_data_;

 public:
  /**
   * @brief Construct a new File object
   * @param filename Name of the file to read
   */
  File(std::string filename);
  ~File();

  /**
   * @brief Read the file and return the entire script line
   * @return std::string File data
   */
  std::string Read() const;
};

/**
 * @brief Exception thrown when file is not opened or does not exist
 */
class FileNotOpenedException : public std::exception {
 public:
  const char *what() const noexcept override { return "File Not Opened"; }
};

typedef std::shared_ptr<File> FilePtr;

#endif