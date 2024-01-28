#include <sstream>
#include "helpers.hpp"

void Helpers::File::closeFile() {
  if (datafile.is_open())
    datafile.close();
}
Helpers::File::File(char *path) : datafile(std::ifstream(path)) {}
Helpers::File::~File() { closeFile(); }
std::vector<std::string> Helpers::File::getLines() {
  std::string line;
  std::vector<std::string> store;
  while (std::getline(datafile, line)) {
    store.push_back(line);
  }
  closeFile();
  return store;
}
bool Helpers::File::isOpen() { return datafile.is_open(); }

void Helpers::checkArgs(int argc) {
  if (argc != 2) {
    std::cout << "missing file path: " << argc << "\n";
    exit(1);
  }
}

// https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> Helpers::split(const std::string& s, char delimeter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}
