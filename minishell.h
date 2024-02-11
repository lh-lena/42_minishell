/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:07:31 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/11 22:40:18 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_command
{
	char				**cmd;
	char				**redir;
	struct s_command	*next;
}	t_command;

typedef struct s_tocken
{
	char			*begin;
	char			*end;
	struct s_tocken	*next;
}	t_tocken;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char		*input;
	t_command	*cmd;
	t_env		*env_lst;
	int			pipes_nb;
	int			cmd_nb;
	int			**pipe_fds;
	int			fd_inp;
	int			fd_outp;
	int			exit_status;
	char		*exit_c;
	size_t		len;
	char		**new_envp;
}	t_data;

void		minishell(t_data *data);
t_command	*parse_input(t_data *data);
t_tocken	*get_tockens(char *str);
int			is_whitespace(char c);
int			find_next_del(char *str);
char		**create_arr_for(t_tocken *lst, char type);
void		add_cmd(t_command **lst, t_command *node);
void		free_tockns_lst(t_tocken *lst);
int			is_pipe(t_tocken *tkn);
int			is_redir(t_tocken *tkn);
void		*malloc_error(void);
void		free_array(int **arr, int size);
void		free_command_lst(t_command *cmd);
int			count_pipes(t_command *lst);
int			execute(char **cmd, char *envp[]);
char		**get_path(char *envp[]);
char		*ft_strcat(char *str1, char *str2);
void		read_heredoc(t_data *data, char *delim, int fd);
char		*file_name(char *str);
char		*get_delim(char *str);
void		open_pipes(t_data *data);
void		close_pipes(t_data *data, int indx);
void		process_command(t_data *data);

#endif
