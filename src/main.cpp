#include <iostream>
#include <string>

int main()
{
  std::string builtin[] = {"type", "echo", "exit"};
  while (true)
  {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    // exit
    if (input == "exit")
    {
      break;
    }

    // echo
    else if (input.substr(0, 4) == "echo")
    {
      if (input == "echo")
      {
        std::cout << "please type something !\n";
        continue;
      }
      std::cout << input.substr(5) << std::endl;
    }

    // type
    else if (input.substr(0, 4) == "type")
    {
      if(input == "type")
      {
        std::cout << "Wrong usage: type `command_name`";
      }
      for (int i = 0; i < builtin->size(); i++)
      {
        if (input.substr(5) == builtin[i])
        {
          std::cout << builtin[i] << " is a shell builtin" << std::endl;
        }
      }
      std::cout << input.substr(5) << ": not found" << std::endl;
    }

    else
    {
      std::cout << input << ": command not found" << "\n";
    }
  }
}
