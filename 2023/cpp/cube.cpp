#include "helpers.hpp"

int main(int argc, char *argv[]) {
  Helpers::checkArgs(argc);
  Helpers::File *file = new Helpers::File(argv[1]);
  std::vector<std::string> lines = file->getLines();
  for (std::string line : lines) {
    // hacks is to just use string splits with different delimiters
    std::vector<std::string> colonSplit = Helpers::split(line, ':'); 
    std::string idStr = Helpers::split(colonSplit[0], ' ')[1];
    int id = std::stoi(idStr);
    std::cout << id << '\n';
  }
  delete file;
  return 0;
}
