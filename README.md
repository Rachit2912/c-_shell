# shellB
A basic command-line tool (REPL) that supports executing commands, handling executable paths, and redirecting output to files. It demonstrates various functionalities such as interpreting commands, executing system commands, and handling input/output redirection.

## Features
- **Command Execution**: Allows you to execute commands from your system's PATH.
- **Echo Command**: Outputs input to the console or redirects it to a file.
- **Custom Command Handling**: Users can define custom commands to be executed.
- **File Output Handling**: Supports redirection of output (standard output and error output) to files.

## Prerequisites
- C++17 or higher
- A C++ compiler (e.g., `g++` or `clang++`)
- Cmake
- vcpkg

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Rachit2912/shellB.git
   ```
2. Navigate to the project directory:
   ```bash
   cd shellB
   ```
3. Compile the program:
   open wsl (windows subsustem for linux) in the shellB folder and run this command :
   ```bash
   vim shellB.sh
   ```
   press 'i' and now edit the vcpkg directory where vcpkg is installed and save by pressing 'esc' => ':wq' 
5. Run the program:
   ```bash
   ./shellB.sh
   ```

## Usage
Once the program starts, you will be prompted with a basic REPL interface. You can input commands, such as:
- *** echo ***: Output text to the console.
- *** pwd *** : Prints the current working directory
- *** cd *** : Changing the directory (supports absolute,relative paths, ./ , ../ , ~ & many more linux file standards)
- *** > / 1>  *** : Output redirection to a file
- *** 2> *** : Error redirection to a file
- *** >> / 1>> *** : Output addition to a file
- *** 2>> *** : Error addition to a file
- *** exit 0 ***: Exit the program
- *** RJ *** : About section of the shell


## How It Works
1. **Command Parsing**: The program reads user input, parses the command, and executes the corresponding action.
2. **Command Mapping**: Commands like `exit`, `echo`, `pwd`, `cd` & `RJ` are mapped to functions using `std::map`.
3. **Path Lookup**: The program can search for executables within directories specified in the system's `PATH` environment variable.
4. **Output Redirection**: Supports `>`, `1>`, `2>`, `>>`, `1>>`, and `2>>` for redirecting output to files.
