#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <functional>
#include<filesystem>
#include<fstream>

std::string get_path(std::string command) {
    std::string newCommand;
    std::string chFront, chBack;
    if (command.front() == '\'' || command.front() == '\"') {
        if (command.size() > 0 && (command.front() == '\'' || command.front() == '\"'))
            newCommand = command.substr(1);
        if (command.size() > 0 && (command.back() == '\'' || command.back() == '\"'))
            newCommand = newCommand.substr(0, newCommand.size() - 1);
        chFront = command.front();
        chBack = command.back();
    }
    else {
        newCommand = command;
        chFront = "";
        chBack = "";
    }


    std::string path_env = std::getenv("PATH");
    if (path_env == "")
    {
        return "";
    }
    std::stringstream ss(path_env);
    std::string path; 

    while (!ss.eof()) {
        std::getline(ss, path, ':');
        std::string abs_path = path + '/' + newCommand;    
        if (std::filesystem::exists(abs_path)) {
            return (path + "/" + chFront + newCommand + chBack);
        }

    }
    return "";
}

void handleExecutablePath(std::string command, std::string argument)
{
    std::string path = get_path(command);
    if (path.empty())
        std::cerr << command << ": command not found" << std::endl;
    else
    {
        std::string execCommand = "exec " + path + " " + argument;
        std::system(execCommand.c_str());
    }
}



int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    //intro:
   std::cout<<R"(
      _            _  _   ____
 ___ | |__    ___ | || | | __ )
/ __|| '_ \  / _ \| || | |  _ \
\__ \| | | ||  __/| || | | |_) |
|___/|_| |_| \___||_||_| |____/
)";
    std::cout << "type RJ for more details!\n";

    // Defining input taken from user
    std::string input;

    // Exit flag for REPL
    bool exit = false;

    // Maps for storing the cmd-action pairs
    std::map<std::string, std::function<void(std::vector<std::string>&)>> cmds;

    // exit action fn:
    cmds["exit"] = [&exit](std::vector<std::string>& args) {
        if (args.size() == 1 && args[0] == "0") {
            exit = true;
            std::exit(0); // Exit program iff "exit 0" is typed
        }
        else if (args.size() == 0) {
            std::cout << "exit : command not found." << std::endl;
        }
        else {
            std::cout << "exit "<<args[0]<<" : command not found." << std::endl;
        }
        };

    // echo action fn:
    //cmds["echo"] = [&input](std::vector<std::string>& args) {

    //    std::string ip = input;
    //    std::string params = input.substr(input.find(' ') + 1,input.size() - input.find(' ') + 1);
    //    std::string result = "";

    //    //bool first = true; // Flag to handle space after the first argument

    //    // Check if the first argument starts with a quote (single or double)
    //    if (ip[5] == '\'') {
    //        for (size_t i = 5; i < ip.length();) {
    //            if (ip[i] == '\'' || ip[i] == '\"') {
    //                ip.erase(i, 1);
    //            }
    //            else { i++; }
    //        }
    //        std::cout << ip.substr(5) << std::endl;
    //    }
    //    //else {
    //    //    // If no quotes, just collapse spaces between words
    //    //    bool first = false;
    //    //    for (size_t i = 5; i < ip.length();) {
    //    //        if (ip[i] == ' ') {
    //    //            if (!first) { first = true; i++; continue; }
    //    //            if (first)
    //    //            {
    //    //                ip.erase(i, 1);
    //    //            }
    //    //        }
    //    //        else { i++; first = false; }
    //    //    }
    //    //}


    //  /*  if ((params.at(0) == '\'') && (params.at(params.size() - 1) == '\''))
    //    {
    //        result = params.substr(1, params.size() - 1);
    //        result = result.substr(0, result.size() - 1);
    //    }*/
    //    else
    //    {
    //        bool space_found = false;
    //        bool apos_start = false;
    //        for (auto c : params)
    //        {
    //            if (c == ' ' && !apos_start) // For any spaces not enclosed by apostrophes
    //            {
    //                if (!space_found)
    //                    space_found = true;
    //                else
    //                    continue; // More spaces -> ignore them
    //            }
    //            else if (space_found)
    //                space_found = false; // No more spaces to handle
    //            if (c == '\"')
    //            {
    //                apos_start = !apos_start;
    //                continue;
    //            }
    //            result += c;
    //        }
    //    std::cout << result << std::endl;
    //    }
    //    };

    //cmds["echo"] = [&input](std::vector<std::string>& args) {
    //    std::string ip = input;
    //    std::string params = input.substr(input.find(' ') + 1, input.size() - input.find(' ') + 1);
    //    std::string result = "";

    //    if (ip[5] == '\'' || ip[5] == '\"') {
    //        bool apos_start = false; // Tracks if inside quotes
    //        for (size_t i = 0; i < ip.size();) {
    //            bool f = true;
    //            while (ip[i] == ' ' && !apos_start) {
    //                if (f) {
    //                    result += " ";
    //                    f = false;
    //                }
    //                i++;
    //            }

    //            if (ip[i] == '\\') {
    //                // Handle backslash escaping
    //                if (i + 1 < ip.size()) {
    //                    result += ip[i + 1];
    //                    i += 2; // Skip the backslash and the next character
    //                }
    //                else {
    //                    result += ip[i];
    //                    i++;
    //                }
    //            }
    //            else if (ip[i] == '\'' || ip[i] == '\"') {
    //                apos_start = !apos_start;
    //                i++;
    //            }
    //            else {
    //                result += ip[i];

    //                i++;
    //            }
    //        }
    //        std::cout << result.substr(5) << std::endl;
    //    }
    //    else {
    //        bool space_found = false;
    //        for (size_t i = 0; i < params.size(); ++i) {
    //            if (params[i] == '\\') {
    //                // Handle backslash escaping
    //                if (i + 1 < params.size()) {
    //                    result += params[i + 1];
    //                    i++; // Skip the backslash
    //                }
    //            }
    //            else if (params[i] == ' ') {
    //                if (!space_found) {
    //                    result += ' ';
    //                    space_found = true;
    //                }
    //            }
    //            else {
    //                result += params[i];
    //                space_found = false;
    //            }
    //        }
    //        std::cout << result << std::endl;
    //    }
    //    };


cmds["echo"] = [&input](std::vector<std::string>& args) {
    std::string ip = input;
    std::string params = input.substr(input.find(' ') + 1, input.size() - input.find(' ') + 1);
    std::string result = "";
    bool writeToFile = true;
    int idx = input.find(">");
    if (idx == -1)writeToFile = false;

    if (!writeToFile) {
        if (ip[5] == '\'' || ip[5] == '\"') {
            bool apos_start = false; // Tracks if inside quotes
            char current_quote = '\0'; // Tracks the type of quote (' or ")
            for (size_t i = 0; i < ip.size();) {
                bool f = true;
                // Skip consecutive spaces outside quotes
                while (ip[i] == ' ' && !apos_start) {
                    if (f) {
                        result += " ";
                        f = false;
                    }
                    i++;
                }

                if (ip[i] == '\\') {
                    // Handle backslash escaping
                    if (current_quote == '"' && i + 1 < ip.size()) {
                        result += ip[i + 1];
                        i += 2; // Skip the backslash and the escaped character
                    }
                    else {
                        result += ip[i];
                        i++;
                    }
                }
                else if (ip[i] == '\'' || ip[i] == '\"') {
                    // Toggle quote state
                    if (!apos_start) {
                        apos_start = true;
                        current_quote = ip[i];
                    }
                    else if (ip[i] == current_quote) {
                        apos_start = false;
                    }
                    else { result += ip[i]; }
                    i++; // Move past the quote
                }
                else {
                    result += ip[i];
                    f = true;
                    i++;
                }
            }
            std::cout << result.substr(5) << std::endl;
        }
        else {
            bool space_found = false;
            for (size_t i = 0; i < params.size(); ++i) {
                if (params[i] == '\\') {
                    // Handle backslash escaping
                    if (i + 1 < params.size()) {
                        result += params[i + 1];
                        i++; // Skip the backslash
                    }
                }
                else if (params[i] == ' ') {
                    if (!space_found) {
                        result += ' ';
                        space_found = true;
                    }
                }
                else {
                    result += params[i];
                    space_found = false;
                }
            }
            std::cout << result << std::endl;
        }
    }
    else {
        std::string output, fileName;
        bool withOne = (input.find("1>")!=-1);
        bool withTwo = (input.find("2>") != -1);
        bool appendOut = (input.find(">>") != -1);
        bool appendOutOne = (input.find("1>>") != -1);
        bool appendError = (input.find("2>>") != -1);

        if(appendOut && appendOutOne){
            if (appendOutOne) {
                int idx2 = input.find("1>>");
                output = input.substr(6, idx2 - 8);
                fileName = input.substr(idx2+4);

            }
            else {
                int idx2 = input.find(">>");
                output = input.substr(6,idx2-9);
                fileName = input.substr(idx2+3);
            }
            std::ofstream outputFile(fileName, std::ios::app); // Open the file to which you want to redirect the output
            if (outputFile.is_open()) {
                outputFile << output << std::endl;
                outputFile.close();
            }


        }

        else {

            if (withTwo) {
                output = input.substr(6, idx - 9);
                fileName = input.substr(idx + 2);

                if(appendError){
                    int idx3 = input.find("2>>");
                    output = input.substr(6, idx3 - 8);
                    fileName = input.substr(idx3 + 4);
                 


                    std::ofstream outFile(fileName,std::ios::app); // Open the file to which you want to redirect the output
                    std::streambuf* cerrbuf = std::cout.rdbuf(); // Save old buffer
                    std::cerr.rdbuf(outFile.rdbuf()); // Redirect std::cout to outFile
                    std::cout << "";

                    std::string cmd = "echo " + output;
                    system(cmd.c_str());


                    std::cerr.rdbuf(cerrbuf);
                    outFile.close();
                    //std::cout << result << std::endl;
                }
                else {
                    std::string cmd = "echo " + output;
                    system(cmd.c_str());


                    std::ofstream outFile(fileName); // Open the file to which you want to redirect the output
                    std::streambuf* coutbuf = std::cout.rdbuf(); // Save old buffer
                    std::cout.rdbuf(outFile.rdbuf()); // Redirect std::cout to outFile
                    std::cout << "";
                    std::cout.rdbuf(coutbuf);
                    outFile.close();
                    //std::cout << result << std::endl;
                }
                
            }
            else
            {

                if (withOne)
                {
                    output = input.substr(6, idx - 9);
                    fileName = input.substr(idx + 2);
                }
                else
                {
                    output = input.substr(6, idx - 8);
                    fileName = input.substr(idx + 2);
                }

                std::ofstream outputFile(fileName);
                if (outputFile.is_open()) {
                    outputFile << output << std::endl;
                    outputFile.close();
                }
            }
        }
        
    }
    };




    // type action fn. : 
    std::set<std::string> builtIns = { "echo","type","pwd","exit" };
    cmds["type"] = [&builtIns](std::vector<std::string>& args) {

        if (args.size() == 1 && builtIns.find(args[0]) != builtIns.end()) {
            std::cout << args[0] << " is a shell builtin" << std::endl;
        }
        else {
            std::string path = get_path(args[0]);
            if (path.empty()) {
                std::cout << args[0] << " not found\n";
            }
            else {
                std::cout << args[0]<< " is " << path << std::endl;
            }
        }
        };

    // pwd action fn. : 
    cmds["pwd"] = [](std::vector<std::string>& args) {
        std::string cmd_path = std::filesystem::current_path();
        std::cout << cmd_path << "\n";
        };


    //cd action fn. : 
    cmds["cd"] = [](std::vector<std::string>& args) {
        std::string target = args[0];
        if (target[0] == '/') {
            if (std::filesystem::exists(target)) {
                std::filesystem::current_path(target);
            }
            if (chdir(target.c_str()) == -1) {
                std::cout << "cd: " << target << ": No such file or directory" << std::endl;
            }
        }

        else if(target[0] == '.'){
            std::string cwd = std::filesystem::current_path().string();
            std::string dir = cwd + '/' + target;
            cwd = std::filesystem::canonical(dir);
                if (chdir(cwd.c_str()) == -1)
                    std::cout << "cd: " << target << ": No such file or directory" << std::endl;
        }

        else if (target[0] == '~') {
            chdir(getenv("HOME"));
        }
        else {
            if (std::filesystem::exists(target)) {
                std::filesystem::current_path(target);
            }
            else{
                std::cout << "cd: " << target << ": No such file or directory" << std::endl;
            }
        }
        };  

    // cat action fn. :
    cmds["cat"] = [&input](std::vector<std::string>& args){
        /* for (auto& arg : args)
         {
             if (!arg.empty() && arg[0] == '\'') {
                 arg = arg.substr(1, arg.size() - 2);
             }
         }

         std::string final_cmd = "cat";
         for (const auto& arg : args) {
             final_cmd += " " + arg;
         }*/
        //std::cerr << "cat is here" << std::endl;
        system(input.c_str());
        };

    // about action fn. :
    cmds["RJ"] = [](std::vector<std::string>& args) {
        std::cout << R"(
      _            _  _   ____
 ___ | |__    ___ | || | | __ )
/ __|| '_ \  / _ \| || | |  _ \
\__ \| | | ||  __/| || | | |_) |
|___/|_| |_| \___||_||_| |____/
)" << std::endl;


        std::cout << "\ta lightweight custom shell completely written in C++\n";
        std::cout << "\toffers a basic command-line interface with essential functionality\n";
        std::cout << "\tideal for developers and tech enthusiasts alike\n";
        std::cout << "\tBuilt with a passion for technology\n";
        std::cout << "\tDeveloped by a tech enthusiast : Rachit Joshi\n";
        std::cout << "\tEnjoy using shellB, Thank You!\n";
        };


    // REPL for shell:
    while (!exit) {

        // prompt sign :
        std::cout << "$ ";


        // Getting the input from the user:
        std::getline(std::cin, input);

        // Stringstream for efficiently differentiating the cmds and args:
        std::stringstream ss(input);
        std::string cmd;
        std::vector<std::string> args;
        

        // Extracting the cmd through the stream:
        ss >> cmd;

        // Extracting the args from the stream:
        std::string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        int i = 1;
        bool quotesOn = false;
        if (input.front() == '\'' || input.front() == '\"')
        {
            quotesOn = true;
            char ch = input.front();
            while (i < input.size() && input[i] != ch)
                i++;
        }
        int separator = input.find(" ", i);
        if (separator == -1)
        {
            separator = input.size();
        }
        std::string command = separator == input.size() ? input : input.substr(0, separator);
        std::string argument = separator < input.size() - 1 ? input.substr(separator + 1) : "";
        



        // Valid cmd found => perform its action:
        if (cmds.find(cmd) != cmds.end()) {
            cmds[cmd](args);
        }
        else {  // Else invalid cmd => not found:
            if (!quotesOn) {
                std::string cmdPath = get_path(command); // checking for exe files 
                if (cmdPath == "") {
                    std::cout << cmd << ": command not found" << std::endl;
                }
                else {
                    std::string command_with_full_path = cmdPath;
                    std::filesystem::path path(command_with_full_path);
                    command_with_full_path = path.filename();

                    for (int argn = 0; argn < args.size(); argn++)
                    {
                        command_with_full_path += " ";
                        command_with_full_path += args[argn];
                    }
                    const char* command_ptr = command_with_full_path.c_str();
                    system(command_ptr);
                    continue;
                }
            }
            else
            {
                handleExecutablePath(command, argument);
            }
        }

    }

    return 0;
}
