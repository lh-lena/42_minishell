# minishell

Minishell is a simple Unix shell emulator written in C language

#### Project done in collaboration with [dzhoka](https://github.com/dzhoka)

The goal of the project is to recreate a simplified version of a Unix shell, capable of interpreting and executing basic shell commands and handling various features such as environment variables, redirection, pipes, and signal handling.

# Features:
* Display a **prompt** when waiting for a new command
* **Command Execution**:
    * Ability to execute commands entered by the user
* **History**:
    * Implement command history functionality
* **Built-in Commands**:
    * Implementation of built-in shell commands such as
    * **cd** with only a relative or absolute path
    * **echo** with option -n
    * **pwd** with no options
    * **export** with no options
    * **unset** with no options
    * **env** with no options or arguments
    * **exit** with no options
* **Redirection**:
    * Support for input and output redirection (<, >, >>) and heredoc (<<)
* **Pipes**:
   * Handling of pipe (|) operations for connecting multiple commands
* **The exit status**:
    * Handling **$?** which should expand to the exit status of the most recently executed foreground pipeline
* **Environment Variables**:
    * Management of environment variables and their manipulation (export, unset)
* **’** (single quotes - prevent from interpreting meta-characters in quoted sequence)
* **"** (double quotes - prevent from interpreting meta-characters in quoted sequence except for $)
* **Signal Handling**:
    * Handling of signals such as ctrl-C, ctrl-D and ctrl-\ which should behave like in bash
* **Error Handling**:
    * Provide informative error messages for user commands

### Installing and running the project:
1. Clone the repository:
```C
    git clone git@github.com:lh-lena/minishell.git minishell
```
2. Navigate to the project directory:
```C
    cd minishell
```
3. Compile and run the project: 
```C
    make && ./minishell
```
or
```C
   make run
```

# Makefile Available Targets:
- `make` or `make all` - compiles minishell
- `make clean` - wipes all object files
- `make fclean` - deletes minishell and all object files
- `make re` - fclean + all
- `make run` - allows project execution without memory leak caused by readline

# Common Instructions
- Take **bash** as a reference
- The project must be written in C
- Function no longer 25 lines
- A single file contains no more 5 functions
- Only one global variable
- Makefile: NAME, all, clean, fclean, re
- Allowed functions:
   readline, rl_clear_history, rl_on_new_line,
   rl_replace_line, rl_redisplay, add_history,
   printf, malloc, free, write, access, open, read,
   close, fork, wait, waitpid, wait3, wait4, signal,
   sigaction, sigemptyset, sigaddset, kill, exit,
   getcwd, chdir, stat, lstat, fstat, unlink, execve,
   dup, dup2, pipe, opendir, readdir, closedir,
   strerror, perror, isatty, ttyname, ttyslot, ioctl,
   getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
   tgetnum, tgetstr, tgoto, tputs



