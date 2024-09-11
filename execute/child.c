/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:43:56 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/09 10:31:22 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	onecommand_output_input_regulator(t_mini *mini, int i, int sq, int dq)
{
	int	fd;

	fd = output_input(mini, i, sq, dq);
	if (fd > 0)
	{
		dup2(fd, 1);
		close (fd);
	}
	if (fd < 0)
		return (0);
	return (1);
}

void	child_procces(t_mini *mini, char **command, int i)
{
	if (g_global_exit == 130)
		return ;
	check_builtin_status(mini);
	if (i == 1 && mini->status == BUILTIN)
	{
		if (!onecommand_output_input_regulator(mini, i, 0, 0))
			return ;
		check_builtin(mini, i);
	}
	else
	{
		mini->pid = fork();
		if (mini->pid == 0)
		{
			ft_signal_regulator(CHILD_P);
			onecommand_output_input_regulator(mini, i, 0, 0);
			if (mini->status != BUILTIN)
				run_cmd(mini, command);
			else
				check_builtin(mini, i);
			exit(g_global_exit);
		}
	}
	return ;
}

void	handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	wait_and_status(t_mini *mini, int i)
{
	pid_t	j;
	int		status;
	t_mini	*temp;

	status = 0;
	temp = mini;
	if (g_global_exit == 130 && status_check2(temp))
	{
		g_global_exit = 1;
		return ;
	}
	while (temp)
	{
		signal(SIGINT, &handler_sigint);
		if (i == 1 && temp->status == BUILTIN)
			break ;
		j = waitpid(temp->pid, &status, 0);
		if (j < 0)
			continue ;
		if (WIFEXITED(status))
			g_global_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global_exit = 128 + WTERMSIG(status);
		temp = temp->next;
	}
}
