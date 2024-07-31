#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

# define NONE 0
# define HEREDOC 1
# define APPEND 2
# define HEREDOCAPPEND 3
# define PIPE 4
# define PIPEHEREDOC 5
# define PIPEAPPEND 6
# define PIPEHEREDOCAPPEND 7
# define BUILTIN 8

typedef struct s_mini
{
	char			*cmd;
	char			*flag_arg;
	char			**env;
	char			**output;
	char			**heredoc;
	char			**input;
	char			**append;
	int				status;
	pid_t			pid;
	struct s_mini	*next;
}	t_mini;

typedef struct s_utils
{
	int	j;
	int	k;
	int	c;
	int	sq;
	int	dq;
	int	a_c;
	int	i_c;
	int	h_c;
	int	o_c;
}	t_utils;

void	take_env(t_mini *mini);
char	**mm_split(char *temp);
void	print_env(t_mini *mini, int status);
int		pp_counter(char *temp, int squotes, int dquotes);
void	utils_struct_init(t_utils *t, char *arg);
void	read_args(t_mini *cmd, char **arg);
void	quote_check(char temp, int *squotes, int *dquotes);
void	take_heredoc(t_utils *t, t_mini *cmd, char *arg);
void	take_append(t_utils *t, t_mini *cmd, char *arg);
void	take_input(t_utils *t, t_mini *cmd, char *arg);
void	take_output(t_utils *t, t_mini *cmd, char *arg);
int		heredoc_count(char *str, int dq, int sq, int status);
int		append_count(char *str, int dq, int sq, int status);
void	ft_allcation_for_struct(t_mini *cmd, t_utils *t);
void	init_mini_struct(t_mini *mini);
void	print_cmd(t_mini *cmd);
void	run_cmd(t_mini *cmd, char **command);

void	heredoc_status_regulator(t_mini *mini, int type);
void	append_status_regulator(t_mini *mini, int type);
void	status_regulator(t_mini *mini);
void	read_and_exec(t_mini *cmd);
void	child_procces(t_mini *cmd, char **command);
void	wait_child(t_mini *cmd);
void	ft_free_dp(char **str);
void	duplicate_default_fd(int fd[2]);
void	close_duplicate_fd(int fd[2]);
void	pipe_checker(int fd[2]);
int		command_list_count(t_mini *mini);
int		output_regulator(t_mini *cmd, int fd[2], int i);
void	non_pipe_output(t_mini *cmd);
int		output_append_checker(t_mini *mini);
int		open_append(t_mini *cmd);
int		open_output(t_mini *cmd);
void	set_input(t_mini *cmd);
int		status_check(t_mini *temp);

#endif