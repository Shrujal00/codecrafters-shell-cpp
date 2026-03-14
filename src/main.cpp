#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <sstream>
#include <unistd.h>


int main()
{
  const char *path_value = std::getenv("PATH");
  const std::string builtin[] = {"type", "echo", "exit"};
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
      if (input == "type")
      {
        std::cout << "Wrong usage: type `command_name`";
      }

      bool found = false;
      for (int i = 0; i < sizeof(builtin) / sizeof(builtin[0]); i++)
      {
        if (input.substr(5) == builtin[i])
        {
          std::cout << builtin[i] << " is a shell builtin" << std::endl;
          found = true;
          break;
        }
      }

      if (!found)
      {
        std::string path_str(path_value);
        std::stringstream ss(path_str);
        std::string segment;
        std::string command = input.substr(5);
        while (std::getline(ss, segment, ':'))
        {
          std::string fullpath = segment + "/" + command;
          if(access(fullpath.c_str(), X_OK == 0))
          {
            std::cout << command << " is " << fullpath;
            found = true;
            break;
          }
        }
      }

      if(!found)
      {
        std::cout << input << ": command not found" << "\n";
      }
    }
  }
