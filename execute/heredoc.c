/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:47 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/20 18:55:09 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc(void)
{
	g_global_exit = 130;
	exit (130);
}

void	ft_heredoc(int fd[2], t_mini *mini, int fd_2[2])
{
	int		i;
	char	*temp;

	i = 0;
	dup2(fd[0], 0);
	while (mini->heredoc[i])
	{
		if (g_global_exit == 999)
		{
			free (temp);
			exit (130);
		}
		temp = readline("> ");
		if (!temp)
			close_heredoc();
		if (g_global_exit == 999)
			continue ;
		if (temp && mini->heredoc[i + 1] == NULL && \
		check_same(mini->heredoc[i], temp) != 0)
			ft_putendl_fd(temp, fd_2[1]);
		if (check_same(mini->heredoc[i], temp) == 0)
			i++;
		free (temp);
	}
	exit (0);
}

void	heredoc_pipe(t_mini *mini, int fd[2])
{
	int	fd_2[2];
	int	status;

	pipe_checker(fd_2);
	mini->pid = fork();
	if (mini->pid == 0)
	{
		ft_signal_regulator(HEREDOC_P);
		ft_heredoc(fd, mini, fd_2);
	}
	close(fd_2[1]);
	dup2(fd_2[0], 0);
	close(fd_2[0]);
	waitpid(mini->pid, &status, 0);
	if (WIFEXITED(status))
		g_global_exit = WEXITSTATUS(status);
}
