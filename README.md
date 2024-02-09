# minishell

Minishell is a simple Unix shell emulator written in C language

Project done in collaboration with @dzhoka

The goal of the project is to recreate a simplified version of a Unix shell, capable of interpreting and executing basic shell commands and handling various features such as environment variables, redirection, pipes, and signal handling.

#Features:
- Display a **prompt** when waiting for a new command.
- **Command Execution**:
    Ability to execute commands entered by the user.
- **History**:
    Implement command history functionality.
- **Built-in Commands**:
    Implementation of built-in shell commands such as
    **cd** with only a relative or absolute path
    **echo** with option -n
    **pwd** with no options
    **export** with no options
    **unset** with no options
    **env** with no options or arguments
    **exit** with no options
- **Redirection**:
    Support for input and output redirection (<, >, >>) and heredoc (<<).
- **Pipes**:
    Handling of pipe (|) operations for connecting multiple commands.
- **The exit status**:
    Handling **$?** which should expand to the exit status of the most recently executed foreground pipeline.
- **Environment Variables**:
    Management of environment variables and their manipulation (export, unset).
- **’** (single quotes - prevent from interpreting meta-characters in quoted sequence)
- **"** (double quotes - prevent from interpreting meta-characters in quoted sequence except for $)
- **Signal Handling**:
    Handling of signals such as ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- **Error Handling**:
    Provide informative error messages for user commands.

#Installing and running the project:
Clone the repository: 
git clone https://github.com/yourusername/minishell.git
Navigate to the project directory: 
cd minishell
Compile the project: 
make
Run the Minishell: 
./minishell

#Makefile Available Targets:
make or make all - compiles minishell
make clean - wipes all object files
make fclean - deletes minishell and all object files
make re - fclean + all

#Common Instructions
- 



