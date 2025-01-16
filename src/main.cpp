#include <iostream>
#include<bits/stdc++.h>
#include<sstream>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  //first prompt : 
  std::cout << "$ ";

  //defining input taken from user 
  std::string input;

  //exit flag for REPL :
  bool exit = false;

  //maps for storing the cmd-action pairs : 
  std::map<std::string, std::function<void(std::vector<std::string>&)>> cmds;
  
  // exit action fn. : 
	cmds["exit 0"] = [](std::vector<std::string>& args) {
		std::cout << "exiting the shell..." << std::endl;
		exit = true;
	}
		
	// echo action fn. :
		cmds["echo"] = [](std::vector > <std::string>& args) {
				for (auto& arg : args)
				{
					std::cout << arg << " ";
				}
				std::cout << std::endl;
		}


  
  //REPL for shell : 
  while (!exit) {

	  // getting the i/p from the user : 
	  std::getline(std::cin, input);

	  // stringstream for efficiently differentiating the cmds and args : 
	  std::stringstream ss(input);
	  std::string cmd;
	  std::vector<std::string> args;

	  // extracting the cmd through the stream : 
	  ss >> cmd;

	  // extracting the args from the stream : 
	  std::string arg;
	  while (ss >> arg) {
		  args.push_back(arg);
	  }

	  // valid cmd. found => perform its action : 
	  if (cmds.find(cmd) != cmds.end()) {
		  cmds[cmd](args);
	  }
	  else //else invalid cmd => not found :
	  {
		  std::cout << cmd << ": command not found" << std::endl;
	  }

	  std::cout << "$";
  }
}
