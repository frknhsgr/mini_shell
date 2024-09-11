/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:10:04 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/08 18:11:50 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_mini *cmd)
{
	int	i;

	i = 0;
	while (cmd->env && cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PATH=", 5))
		{
			return (ft_split(ft_strchr(cmd->env[i], '/'), ':'));
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_mini *cmd, char **command, char **path, int i)
{
	char	*temp;
	char	*temp2;

	path = get_path(cmd);
	if (!path)
	{
		printf("PATH ERROR\n");
		exit(1);
	}
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		temp2 = ft_strjoin(temp, command[0]);
		if (!access(temp2, X_OK))
			return (free(temp), temp2);
		free(temp);
		free(temp2);
	}
	ft_putstr_fd("minishell: ", 2);
	write(2, command[0], ft_strlen(command[0]));
	ft_putstr_fd(": command not found\n", 2);
	g_global_exit = 127;
	exit(127);
	return (NULL);
}

void	run_cmd(t_mini *mini, char **command)
{
	char	*path;

	if (!command[0])
		return ;
	if (check_same(command[0], "") == 0)
		if (execute_error(command[0], 0))
			return ;
	if (strchr(command[0], '/'))
	{
		path = command[0];
		if (ft_isdirectory(path))
			if (execute_error(path, 2))
				return ;
		if (!is_fileordirectory(path))
			if (execute_error(path, 0))
				return ;
		if (access(command[0], X_OK))
			if (execute_error(path, 1))
				return ;
	}
	else
		path = get_cmd_path(mini, command, NULL, -1);
	execve(path, command, mini->env);
}
