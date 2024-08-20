#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "lib/libft/libft.h"

# define NONE 0
# define HEREDOC 1
# define APPEND 2
# define HEREDOCAPPEND 3
# define PIPE 4
# define PIPEHEREDOC 5
# define PIPEAPPEND 6
# define PIPEHEREDOCAPPEND 7
# define BUILTIN 8
# define CHILD_P 9
# define MAIN_P 10
# define HEREDOC_P 11

typedef struct s_mini
{
	char			*arg;
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

extern int	g_global_exit;

void		take_env(t_mini *mini);
char		**mm_split(char *temp);
void		print_env(t_mini *mini, int status);
int			pp_counter(char *temp, int squotes, int dquotes);
void		utils_struct_init(t_utils *t, char *arg);
void		read_args(t_mini *cmd, char **arg);
void		quote_check(char temp, int *squotes, int *dquotes);
void		take_heredoc(t_utils *t, t_mini *cmd, char *arg);
void		take_append(t_utils *t, t_mini *cmd, char *arg);
void		take_input(t_utils *t, t_mini *cmd, char *arg);
void		take_output(t_utils *t, t_mini *cmd, char *arg);
int			heredoc_count(char *str, int dq, int sq, int type);
int			append_count(char *str, int dq, int sq, int type);
void		ft_allcation_for_struct(t_mini *cmd, t_utils *t);
void		init_mini_struct(t_mini *mini);
void		print_cmd(t_mini *cmd);
void		run_cmd(t_mini *cmd, char **command);

void		heredoc_status_regulator(t_mini *mini, int type);
void		append_status_regulator(t_mini *mini, int type);
void		status_regulator(t_mini *mini);
void		ft_executer(t_mini *mini, char **command, int i, int fd[2]);
void		read_and_exec(t_mini *cmd, int i);
char		**execve_command(t_mini *temp, char **temp2);
void		child_procces(t_mini *cmd, char **command, int i);
void		wait_child(t_mini *cmd);
void		execute_pipe(t_mini *mini, char **command, int i);
void		ft_free_dp(char **str);
void		duplicate_default_fd(int fd[2]);
void		close_duplicate_fd(int fd[2]);
void		pipe_checker(int fd[2]);
int			command_list_count(t_mini *mini);

void		onecommand_output_input_regulator(t_mini *mini, int i, int sq, int dq);
void		output_input_regulator(t_mini *mini, int i, int fd[2]);
int			output_append_checker(t_mini *mini);
int			ft_open_output(t_mini *mini, int i);
int			ft_open_append(t_mini *mini, int i);
int			ft_open_input(t_mini *mini, int i);

int			status_check(t_mini *temp);
void		heredoc_pipe(t_mini *mini, int fd[2]);
void		ft_heredoc(int fd[2], t_mini *mini, int fd_2[2]);
int			check_same(char *s1, char *s2);
void		fderror_1(char *str);
void		fderror_2(char *str);
int			ft_isdirectory(const char *str);
int			is_fileordirectory(const char *str);

void		ft_signal_regulator(int status);
void		ft_main_signal(int signal);
void		ft_heredoc_signal(int signal);

char		*make_lower(char *str);
int			builtin_strcmp(char *s1, char *s2);
void		check_builtin_status(t_mini *mini);
void		check_builtin(t_mini *mini, int i);
void		cd(t_mini *mini, char *newlocation);
int			cd_case1(t_mini *mini, char **newlocation, char **newpwd, char *oldpwd);
void		set_newlocation(char *oldpwd, char **newpwd, char *newlocation);
char		*get_oldpwd(t_mini *mini);
int			cd_case2(t_mini *mini, char **newpwd, char **newlocation, char *oldpwd);
char		*get_home(t_mini *mini);
int			chdir_situation(char *newpwd, char *newlocation, char *oldpwd);
void		set_pwd(t_mini *mini, char *oldpwd, char *newpwd);
void		set_newpwd2(char *newpwd, char **newpwd2);
void		set_newpwd(t_mini *mini, char *newpwd, char *newpwd2, int i);
void		set_oldpwd(t_mini *mini, char *oldpwd, int i);
void	    pwd();
void    	ft_exit(t_mini *mini, int i);
int			ft_isnumeric(char *str);
int			ft_arg_count(char **str);
int			exit_with_arg(t_mini *mini, int j, char **arg);
void		exit_with_error(t_mini *mini, char **arg);
void		ft_echo(t_mini *mini);
void		echo_with_arg(t_mini *mini);
void		echo_flag_control(char **arg, int *i);
int			flag_control(char *arg);

#endif