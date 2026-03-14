#include <iostream>
#include <string>

int main() {

  std::string command;

  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::cout << "$ ";
  
  std::cin >> command;

  std::cout << command << ": command not found";
  
}
