/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:15:18 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/09 11:22:58 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	struct stat	status;

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

void	ft_free_dp(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}
