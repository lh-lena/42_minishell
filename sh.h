#ifndef SH_H
# define SH_H

# include <unistd.h> // read write close	 fork getcwd chdir execve dup dup2 pipe 
# include <stdio.h> // printf 
# include <stdlib.h> // malloc free exit
# include <fcntl.h> // open 
# include <sys/wait.h> // wait waitpid wait3 wait4
# include <signal.h> // signal kill 
# include <sys/stat.h> // stat lstat fstat 
# include <dirent.h> // opendir readdir closedir
# include <string.h> // strerror
# include <errno.h> // errno
# include <term.h> // termcap 
# include <readline/readline.h> // readline 
# include <readline/history.h> 
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcsetattr tcgetattr 
# include <curses.h> // tgetnum tgetflag tgetstr tgoto 
# include <term.h> // tgetent
# include <sys/types.h>
// # include "../libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char 	*prompt; // readed prompt line
	char 	*pwd; // cur path
	char	**argv; // split input
	char	**envp;
}	t_data;

// string utils
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
size_t	ft_arrsize(char	**arr);
void	print_arr(char **arr);

// print utils
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// linked list utils
t_env	*ft_lstnew(char	*str);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_delnode(t_env **lst, char *name);
size_t	ft_lstsize(t_env *lst);
void	print_lst(t_env *lst);

void	panic(char	*s);
void	manage_signal(void);

// parser


// -- handle_builtins --
// history
void	create_history(t_data *data);

// input
void	parse_input(t_data	*input);
void	check_cmd(t_data *input);

// cd (Changes current working directory, updating PWD and OLDPWD | chdir)

// echo -n (Prints arguments separated with a space followed by a new line| -n | write)

// export (Adds/replaces variable in environment)

// pwd (Prints current working directory | no parameters | getcwd)

// env (Prints environment | write)
void	env_tr(t_data	*data);
t_env	*ft_getenv(char **envp);

// unset (Removes variable from environment | $VAR)

// exit
int		is_exit(char *input);
void	exit_handler(void);

#endif