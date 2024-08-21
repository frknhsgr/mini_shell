/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:18:11 by fhosgor           #+#    #+#             */
/*   Updated: 2024/08/21 16:26:58 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipe(t_mini *mini, char **command, int i)
{
	int	pipe[2];

	pipe_checker(pipe);
	mini->pid = fork();
	if (mini->pid == 0)
	{
		ft_signal_regulator(CHILD_P);
		close(pipe[0]);
		output_input_regulator(mini, i, pipe);
		close(pipe[1]);
		check_builtin_status(mini);
		if (mini->status != BUILTIN)
			run_cmd(mini, command);
		else
			check_builtin(mini, i);
		exit (g_global_exit);
	}
	close(pipe[1]);
	dup2(pipe[0], 0);
	close(pipe[0]);
}

char	**execve_command(t_mini *temp, char **temp2)
{
	char	**ret;
	int		i;

	i = 0;
	if (temp->flag_arg)
	{
		temp2 = ft_split(temp->flag_arg, ' ');
		while (temp2[i])
			i++;
	}
	if (temp->cmd != NULL)
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	if (temp->cmd != NULL)
		ret[0] = ft_strdup(temp->cmd);
	i = 0;
	while (temp2 && temp2[i] && ++i)
		ret[i] = ft_strdup(temp2[i - 1]);
	if (i == 0 && temp->cmd == NULL)
		ret[0] = NULL;
	else
		ret[i + 1] = NULL;
	return (ft_free_dp(temp2), ret);
}

int	status_check(t_mini *temp)
{
	if (temp->status == PIPE || temp->status == PIPEAPPEND)
		return (1);
	else if (temp->status == HEREDOC || temp->status == HEREDOCAPPEND \
	|| temp->status == PIPEHEREDOC || temp->status == PIPEHEREDOCAPPEND)
		return (2);
	else
		return (3);
}

void	ft_executer(t_mini *mini, char **command, int i, int fd[2])
{
	if (status_check(mini) == 1)
	{
		if (mini->heredoc[0])
			heredoc_pipe(mini, fd);
		if (g_global_exit == 130)
			return ;
		execute_pipe(mini, command, i);
	}
	else if (status_check(mini) == 2)
	{
		heredoc_pipe(mini, fd);
		if (g_global_exit == 130)
			return ;
		execute_pipe(mini, command, i);
	}
	else
	{
		if (mini->heredoc[0])
			heredoc_pipe(mini, fd);
		if (g_global_exit == 130)
			return ;
		child_procces(mini, command, i);
	}
}

void	read_and_exec(t_mini *cmd, int i)
{
	t_mini	*temp;
	char	**command;
	int		fd[2];

	temp = cmd;
	duplicate_default_fd(fd);
	while (temp)
	{
		command = execve_command(temp, NULL);
		ft_executer(temp, command, i, fd);
		ft_free_dp(command);
		temp = temp->next;
	}
	close_duplicate_fd(fd);
	wait_child(cmd);
}
