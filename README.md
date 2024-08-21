# Simple Shell

## Introduction

Welcome to the Simple Shell project, developed as part of the ALX Software Engineering program. This project is a simple Unix shell that mimics the functionalities of a standard command-line interpreter. It was built to deepen our understanding of system calls, process management, and input/output handling in C.

## Repository Contents

Below are the key files and their functionalities:

- **builtin_emu.c**: Contains the implementation of built-in shell commands.
- **builtin_emu2.c**: Additional built-in commands handling.
- **chain.c**: Handles command chaining, allowing multiple commands to be executed in sequence.
- **env.c**: Manages environment variables within the shell.
- **env2.c**: Additional functionalities for managing environment variables.
- **func1.c**: Contains core utility functions used across the shell.
- **func2.c**: Additional utility functions for shell operations.
- **func3.c**: More utility functions.
- **func4.c**: Further utility functions.
- **getline.c**: Custom implementation of the `getline` function for reading input.
- **hsh.c**: The main entry point for the shell.
- **info.c**: Manages shell information and state.
- **io_fun.c**: Handles input/output operations.
- **main.c**: The main logic of the shell, managing the overall flow.
- **more_func.c**: Contains additional helper functions.
- **more_func2.c**: More helper functions.
- **more_func3.c**: Even more helper functions.
- **path.c**: Handles the searching and execution of commands in the system's PATH.
- **shell.h**: Header file containing all function prototypes and struct definitions.
- **string_error.c**: Handles string manipulation and error reporting.
- **string_list.c**: Manages linked lists of strings.
- **string_list2.c**: Additional linked list management functions.

### Temporary Swap Files

These files are swap files generated by the text editor and can be ignored:

- `.func1.c.swp`
- `.getline.c.swp`
- `.more_func2.c.swp`

### Executable

- **hsh**: The compiled executable for the Simple Shell.

### Core Dumps

- **vgcore.1643**: This file is likely a core dump generated during development and can be ignored or used for debugging purposes.

## How to Compile and Run

To compile the Simple Shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

To start the shell, run the compiled executable:
```bash
./hsh
```

## Usage

Once the shell is running, you can enter commands as you would in a standard Unix shell. The shell supports built-in commands, as well as executing programs found in the system's PATH.

## Features

- **Built-in Command Handling**: Supports basic built-in commands like `cd`, `exit`, and `env`.
- **Environment Variable Management**: Allows setting and unsetting of environment variables.
- **Command Chaining**: Execute multiple commands in sequence.
- **Custom `getline` Implementation**: A custom implementation of the `getline` function to handle input efficiently.

## Authors

This project was developed by [Samia Asim](https://github.com/Samia8Asim) and [Rawan omer](https://github.com/rawan-omer) as part of the ALX Software Engineering program.
