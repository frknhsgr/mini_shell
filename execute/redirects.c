/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:57:08 by fhosgor           #+#    #+#             */
/*   Updated: 2024/09/13 14:09:27 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_input(t_mini *mini, int i)
{
	int			fd;
	static int	j;

	if (!mini->input || !mini->input[j])
		return (1);
	if (mini->input[j])
	{
		fd = open(mini->input[j], O_RDONLY, 0644);
		if (fd == -1 && (i != 1 || mini->status != BUILTIN))
			fderror_1(mini->input[j]);
		else if (fd == -1 && i == 1)
		{
			fderror_2(mini->input[j]);
			return (-1);
		}
		if (mini->input[j + 1])
			close (fd);
		j++;
	}
	if (mini->input[j] == NULL)
	{
		dup2(fd, 0);
		close(fd);
		j = 0;
	}
	return (1);
}

int	ft_open_output(t_mini *mini, int i)
{
	int			fd;
	static int	j;

	fd = 0;
	if (!mini->output || !mini->output[j])
		return (1);
	if (mini->output[j])
	{
		fd = open(mini->output[j], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1 && (i != 1 || mini->status != BUILTIN))
			fderror_1(mini->output[j]);
		else if (fd == -1 && i == 1)
		{
			fderror_2(mini->output[j]);
			return (-1);
		}
		if (mini->output[j + 1])
			close(fd);
		j++;
	}
	if (mini->output[j] == NULL)
		j = 0;
	return (fd);
}

int	ft_open_append(t_mini *mini, int i)
{
	int			fd;
	static int	j;

	fd = 0;
	if (!mini->append || !mini->append[j])
		return (1);
	if (mini->append[j])
	{
		fd = open(mini->append[j], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1 && (i != 1 || mini->status != BUILTIN))
			fderror_1(mini->append[j]);
		else if (fd == -1 && i == 1)
		{
			fderror_2(mini->append[j]);
			return (-1);
		}
		if (mini->append[j + 1])
			close(fd);
		j++;
	}
	if (mini->append[j] == NULL)
		j = 0;
	return (fd);
}

int	output_input(t_mini *mini, int i, int sq, int dq)
{
	int	fd;
	int	j;
	int	flag;

	j = -1;
	flag = 1;
	fd = 0;
	while (mini->arg[++j])
	{
		quote_check(mini->arg[j], &sq, &dq);
		if (flag == -1 || fd == -1)
			return (-1);
		if (if_input(mini, j, sq, dq))
			flag = ft_open_input(mini, i);
		if (if_heredoc(mini, j, sq, dq))
			j++;
		if (if_output(mini, j, sq, dq))
			fd = ft_open_output(mini, i);
		if (if_append(mini, j, sq, dq))
		{
			fd = ft_open_append(mini, i);
			j++;
		}
	}
	return (fd);
}

void	output_input_regulator(t_mini *mini, int i, int fd[2])
{
	close (fd[0]);
	if (output_append_checker(mini) == 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		onecommand_output_input_regulator(mini, i, 0, 0);
	}
	else
		onecommand_output_input_regulator(mini, i, 0, 0);
}
