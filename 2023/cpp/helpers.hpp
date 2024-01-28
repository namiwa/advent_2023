#ifndef __HELPERS__HPP
#define __HELPERS__HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Helpers {
  class File {
  private:
    std::ifstream datafile;
    void closeFile();
  public:
    File(char *path);
    ~File();
    std::vector<std::string> getLines();
    bool isOpen();
  };
  
  void checkArgs(int argc);
  std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif
