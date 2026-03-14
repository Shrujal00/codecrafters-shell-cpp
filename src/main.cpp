#include <iostream>
#include <string>

int main() {
  while(true) 
  {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "exit")
    {
      break;
    }

    
    std::cout << input << ": command not found" << "\n";
  }  
}
