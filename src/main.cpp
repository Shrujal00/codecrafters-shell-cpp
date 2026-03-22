#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <climits>

namespace fs = std::filesystem;


std::string find_in_path(const std::string &command, const char *path_value)
{
  std::string path_string(path_value);
  std::stringstream ss(path_string);
  std::string segment;

  while (std::getline(ss, segment, ':'))
  {
    std::string fullpath = segment + "/" + command;
    if (std::filesystem::exists(fullpath) && access(fullpath.c_str(), X_OK) == 0)
    {
      return fullpath;
    }
  }

  return "";
}

int main()
{
  const char *path_value = std::getenv("PATH");
  const std::string builtin[] = {"type", "echo", "exit", "pwd", "cd"};
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

    //sgfunc
    else if(input == "sg")
    {
      std::cout << "Hello Shrujal how are you doing ??" << std::endl;
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
          if (std::filesystem::exists(fullpath) &&
              access(fullpath.c_str(), X_OK) == 0)
          {
            std::cout << command << " is " << fullpath << std::endl;
            found = true;
            break;
          }
        }
      }

      if (!found)
      {
        std::cout << input.substr(5) << ": not found" << "\n";
      }
    }
    // pwd
    else if (input == "pwd")
    {
      char buffer[PATH_MAX];
      std::string pwd = getcwd(buffer, PATH_MAX);
      std::cout << pwd << std::endl;
    }
    // IF the command is a executable then run it
    else if (find_in_path(input.substr(0, input.find(' ')), path_value) != "")
    {
      std::string args[100];
      int argsc = 0;
      std::stringstream ss(input);
      std::string token;

      while (ss >> token)
      {
        args[argsc] = token;
        argsc++;
      }

      const char* argv[101];
      for(int i = 0; i < argsc; i++)
      {
        argv[i] = args[i].c_str();
      }

      argv[argsc] = nullptr;


      pid_t pid = fork();
      if (pid == 0)
      {
         execvp(args[0].c_str(), (char* const*)argv);
      } else {
        wait(nullptr);
      }
    }

    //cd
    if (input.substr(0,2) == "cd")
    {
      fs::path currentPath = fs::current_path();
      std::string new_path = input.substr(3);

      // fs::current_path(new_path);

      try
      {
        fs::current_path(new_path);
        // std::cout << new_path << std::endl;
        continue;
      }
      catch(fs::filesystem_error const& ex)
      {
        std::cerr << "cd: " << new_path << ": No such file or directory" << std::endl;
      }


    }
    

    // else
    // {
    //   std::cout << input << ": command not found" << "\n";
    // }
  }
}