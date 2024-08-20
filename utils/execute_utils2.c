/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:10 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/20 18:52:24 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_same(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 \
	&& ft_strncmp(s2, s1, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}

int	command_list_count(t_mini *mini)
{
	int		i;
	t_mini	*temp;

	i = 0;
	temp = mini;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
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
