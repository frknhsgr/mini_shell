/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:27:36 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/04 18:30:52 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duplicate_default_fd(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	close_duplicate_fd(int fd[2])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	pipe_checker(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(127);
	}
}

int	check_same(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 \
	&& ft_strncmp(s2, s1, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}

int	execute_error(char *command, int i)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	if (i == 0)
	{
		ft_putendl_fd(": No such file or directory", 2);
		g_global_exit = 127;
		return (1);
	}
	else if (i == 1)
	{
		ft_putendl_fd(": Permission denied", 2);
		g_global_exit = 126;
		return (1);
	}
	else if (i == 2)
	{
		ft_putendl_fd(": is a directory", 2);
		g_global_exit = 126;
		return (1);
	}
	return (0);
}
