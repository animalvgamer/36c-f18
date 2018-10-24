#include <iostream>
#include <limits>
#include <vector>

#include "trees.h"

int main() {
  SiblingTree<int> tree;
  tree.insertItem({{}}, 15);
  tree.insertItem({{}}, 21);
  tree.insertItem({{}}, 56);
  tree.insertItem({{0}}, 91);
  tree.insertItem({{0}}, -5);
  tree.insertItem({{1}}, 6);


  while (true) {
    std::cout << tree << std::endl;

    char command = '\0';

    std::cout << "[i]nsert, [r]emove, [s]et:" << std::endl;

    std::cin >> command;
    if (std::cin.eof()) break;
    switch (command) {
     case 'i':
     case 'r':
     case 's':
      break;
     default:
      std::cout << "invalid input detected" << std::endl;
      continue;
    }

    std::cout << "Enter path, mark end with -1" << std::endl;
    size_t path_step;
    std::vector<size_t> path;
    while (std::cin >> path_step && path_step != -1) {
      path.push_back(path_step);
    }
    if (std::cin.fail()) {
      std::cout << "Bad number detected, try again!" << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    int value;
    switch (command) {
     case 'i':
      std::cout << "Enter value to insert: ";
      std::cin >> value;
      if (std::cin.fail()) {
        std::cout << "Bad number detected, try again!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      tree.insertItem({path}, value);
      break;
     case 'r':
      tree.removeNode({path});
      break;
     case 's':
      std::cout << "Enter value to set node to: ";
      std::cin >> value;
      if (std::cin.fail()) {
        std::cout << "Bad number detected, try again!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      tree.getItem({path}) = value;
      break;
    }
  }
}
