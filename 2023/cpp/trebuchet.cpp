#include <algorithm>
#include <cctype>
#include <locale>
#include <iostream>
#include <fstream>
#include <string>

// well known that trim is not built in support in both c and cpp

inline void ltrim(std::string &s, unsigned char &target) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&target](unsigned char ch) {
    return ch != target;
  }));
}


inline void rtrim(std::string &s, unsigned char &target) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [&target](unsigned char ch) {
    return ch != target;
  }).base(), s.end());
}

// trim string in place
inline void trim(std::string &s, unsigned char &target) {
  rtrim(s, target);
  ltrim(s, target);
}

// main function docs: https://learn.microsoft.com/en-us/cpp/cpp/main-function-command-line-args?view=msvc-170
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "missing file path: " << argc << "\n";
    return 1;
  }

  // cpp text file reading: https://cplusplus.com/doc/tutorial/files/
  std::string line;
  std::ifstream datafile (argv[1]);
  long total = 0;
  if (datafile.is_open()) {
    while (std::getline(datafile, line)) {
      int first = -1;
      int last = -1;
      for (auto c : line) {
        if (std::isdigit(c) && first == -1) {
          first = int(c) - 48;
        }
        if (std::isdigit(c)) {
          last = int(c) - 48;
        }
      }
      std::cout << "debug line: " << line << " size: " << line.size() << " first: " << first << " last: " << last << std::endl;
      total += (10 * first) + last;
    }
  }
  std::cout << "answer is: " << total << std::endl;
  return 0;
}
