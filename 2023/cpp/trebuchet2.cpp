#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>

class Node {
public:	
	Node* children[26];
	bool terminal;
	char value;
	Node(): Node('\0', true) {}
	
	Node(char val, bool isTerminal)
		: value(val)
		, terminal(isTerminal)
	{}

	~Node() {
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) {
				children[i]->~Node();
				delete children[i];
			}
			free(children);
		}
	}

};

class Trie {
	Node* root;
	
public:

	Trie(): root(new Node()) {}

	~Trie() {
		if (!root) return;
		for (Node* node : root->children) {
			if (node) {
				node->~Node();
			}
		}
		free(root->children);
		delete root;
	}

	void insert(std::string text) {
		Node* currRoot = root;
		for (char c : text) {
			int key = int(c) - 97;
			if (!currRoot->children[key]) {
				currRoot->children[key] = new Node();
			}
			currRoot->children[key]->value = c;
			currRoot->children[key]->terminal = false;
			currRoot = currRoot->children[key];
		}	
	}

	bool search(std::string target) {
		Node* currRoot = root;
		for (char c : target) {
			int key = int(c) - 97;
			if (!currRoot->children[key]) return false;
			currRoot = currRoot->children[key];
		}
		return true;
	}
};

std::unordered_map<std::string, int> mapper = {
    {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

// main function docs:
// https://learn.microsoft.com/en-us/cpp/cpp/main-function-command-line-args?view=msvc-170
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "missing file path: " << argc << "\n";
    return 1;
  }

	// init helpers
	Trie trie = Trie();
	for (auto m : mapper) {
		trie.insert(m.first);
	}

  // cpp text file reading: https://cplusplus.com/doc/tutorial/files/
  std::string line;
  std::ifstream datafile(argv[1]);
  long total = 0;
  if (datafile.is_open()) {
		// use trie to prune window search space --> check if exact match is found 
		// discard suffix chars if it fails to be in trie search space
    while (std::getline(datafile, line)) {
      int first = -1;
      int last = -1;
      std::string window = "";
      for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (std::isdigit(c)) {
          window = "";
          last = int(c) - 48;
        } else {
          window += c;
					std::cout << "internal debug: currentWindow: " << window;
					if (mapper.count(window)) {
						last = mapper[window];
						window = c;
					} else if (!trie.search(window)) {
						// don't discard whole string
						while (window.size() && !trie.search(window)) {
							window.erase(0, 1);
						}
						if (!trie.search(window)) {
							window.erase(0, 1);
						}
					}
					std::cout << " afterWindow: " << window << '\n';
        }
        if (first == -1 && last != -1) {
          first = last;
        }
      }
      std::cout << "debug line: " << line << " size: " << line.size()
                << " first: " << first << " last: " << last << std::endl;
      total += (10 * first) + last;
    }
  }
  std::cout << "answer is: " << total << std::endl;
	trie.~Trie();
  return 0;
}
