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
	char			*name; // (malloc)
	char			*value; // (malloc)
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char 	*input; // readed prompt line
	char	**argv; // split input (malloc)
	int		exit_status;
	char	**envp;
	t_env	*env_lst; // copied envp (malloc)
}	t_data;

// libft
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nitems, size_t size);
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

// str_utils
int		ft_isspace(int c);
int		ft_issign(int c);
int		ft_isdigit_str(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	str_copy(char *s1, char *s2);

// arr_utils
size_t	ft_arrsize(char	**arr);
size_t	ft_arrlen(char **arr);
void	print_arr(char **arr);
void	ft_free_arr(char **arr);

// print_utils
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// list_utils
t_env	*ft_new_node_env(char	*str);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_delnode_env(t_env **lst, char *name);
size_t	ft_lstsize_env(t_env *lst);
void	ft_print_lst_env(t_env **lst, int arg);
void	ft_free_lst_env(t_env *lst);
void	ft_free_node_env(t_env *node);

// free
void	ft_free_data(t_data	*data);

// sh_utils
void	panic(char	*s);
void	ft_print_new_prompt(void);

// execute
void	execve_tr(t_data *data);

// -- handle_builtins -- 
// history
void	create_history(t_data *data);

// input

// cd_cmd (Changes current working directory, updating PWD and OLDPWD | chdir)
void	cd_cmd(t_data *data, char **arg);

// echo -n (Prints arguments separated with a space followed by a new line| -n | write)

// export (Adds/replaces variable in environment)
int		is_quotes(char *value);
void	export(t_data *data, char **input);
char	*export_execution(t_data *data, char *input);
char	*get_replaced_str(t_env *envp, char *s);
char	*replace_var_value(t_env *envp, char *s, char **var_names, size_t value_len);
void	replace_str(char *new, t_env *envp, char *s, char **var_names);
char	*env_get_var_value(t_env *envp, char *name);
void	env_replace_or_create_node(t_env *envp, char *input);

char	**get_var_name_arr(char *s, char c);
char	**var_split(char *s, char c);

// export_utils
int		isvalid_export_input(char *str);
int		isvalid_var_name_str(char *str);
int		isvalid_var_name_char(int c);

// pwd (Prints current working directory | no parameters | getcwd)
void	pwd_cmd(t_data *data);

// env (Prints environment | write)
void	env_print(t_data *data);
t_env	*ft_getenv(char **envp);
int		env_update_val(t_env *envp, char *name, char *value);
size_t	env_isvar_name(t_env *envp, char *name);

// unset (Removes variable from environment | $VAR)
void	unset(t_data *data, char **input);

// exit
int		is_exit(t_data *data);
void	exit_handler(t_data *data);

// signal
// void	manage_signal(void);

#endif