/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:40:56 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/11 20:13:41 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <unistd.h> // read write close fork getcwd chdir execve dup dup2 pipe
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
# include "minishell.h"
# include "./libft/libft.h"

extern int g_sig_status;

// str_utils
int		ft_isspace(int c);
int		ft_issign(int c);
int		ft_isdigit_str(char *s);
int		is_whitespace_str(char *str);
void	str_copy(char *s1, char *s2);
int		isspecial_char(int c);
int		handle_name(int	c);

// arr_utils
size_t	ft_arrsize(char	**arr);
size_t	ft_arrlen(char **arr);
void	print_arr(char **arr);
void	ft_free_arr(char **arr);

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
void	ft_free(char **str);

// error_handle
void	put_error(t_data *data, char *msg, int er_num);
void	put_error_arg(t_data *data, char *msg, char *arg, char *msg2, int er_n);

// execute
void	execve_tr(t_data *data, char **arr);

// heredoc
void	read_heredoc(t_data *data, char *delim, int fd);

// -- handle_builtins --
// history
void	create_history(t_data *data);

// cd_cmd (Changes current working directory, updating PWD and OLDPWD | chdir)
void	cd_builtin(t_data *data, char **arr);

// echo -n (Prints arguments separated with a space followed by a new line| -n | write)
void	echo_builtin(t_data *data, char **arr);

// export (Adds/replaces variable in environment)
int		is_quotes(char *value);
void	export(t_data *data, char **input);
char	*expand_str(t_data *data, char *input);
char	*get_replaced_str(t_data *data, char *s);
char	*replace_var_value(t_data *data, char *s, char **var_nms, size_t val_l);
void	replace_str(char *new, t_data *data, char *s, char **var_names);
char	*env_var_value(t_env *envp, char *str);
void	env_replace_or_create_node(t_env *envp, char *input);

char	**get_var_name_arr(char *s, char c);
char	**var_split(char *s, char c);

// edit_qoutes_str
char	*substitute_str(t_data *data, char *str);
char	*copy_modified_str(t_data *data, char *str, size_t len);

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
size_t	env_isvar_name(t_env *envp, char *str);
char	*copy_var_name(char *str);
char	**new_envp(t_data *data);

// unset (Removes variable from environment | $VAR)
void	unset(t_data *data, char **input);

// exit
int		is_exit(t_data *data);
void	exit_handler(t_data *data);

// -- handel signals -- Crtl+C Crtl+D Ctrl+'\'
void	new_line_c(int sig_num);
void	new_line_h(int sig_num);
void	sig_handle(int sig_num);

#endif
