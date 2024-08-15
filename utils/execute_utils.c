#include "../minishell.h"

int	ft_isdirectory(const char *str)
{
	struct stat	status;

	if (stat(str, &status) != 0)
		return (0);
	return (S_ISDIR(status.st_mode));

}

int	is_fileordirectory(const char *str)
{
	struct stat status;

	if (stat(str, &status) != 0)
		return (0);
	return (S_ISREG(status.st_mode));
}

void	fderror_1(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (ft_isdirectory(str))
	{
		ft_putstr_fd(": Is a directory\n", 2);
		exit(1);
	}
	else if (!is_fileordirectory(str))
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	else if (access(str, R_OK))
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	g_global_exit = 1;
	exit (1);
}

void	fderror_2(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (ft_isdirectory(str))
		ft_putstr_fd(": Is a directory\n", 2);
	else if (!is_fileordirectory(str))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (access(str, R_OK))
		ft_putstr_fd(": Permission denied\n", 2);
	g_global_exit = 1;
}

int	command_list_count(t_mini *mini)
{
	int	i;
	t_mini *temp;

	i = 0;
	temp = mini;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_free_dp(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return ;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	ft_main_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_exit = 1;
	}
}

void	ft_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_global_exit = 999;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	ft_signal_regulator(int status)
{
	if (status == MAIN_P)
	{
		signal(SIGINT, &ft_main_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == CHILD_P)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (status == HEREDOC_P)
	{
		signal(SIGINT, &ft_heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
}