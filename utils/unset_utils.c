/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:49:52 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 14:33:33 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_typo(t_mini *mini, char **keep, int *i, int *control)
{
	int	j;

	j = 0;
	while (keep[(*i)][j])
	{
		if (!(ft_isalnum(keep[(*i)][j])) && keep[(*i)][j] != '#'
			&& keep[(*i)][j] != '_')
		{
			export_err_msg(delete_quotes(ft_strdup(keep[(*i)]), \
			mini, 0, 0), 1);
			(*i)++;
			(*control) = 1;
			g_global_exit = 1;
			break ;
		}
		j++;
	}
}

int	count_unsets(char **str, t_mini *mini, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (mini->env[i])
	{
		while (str[j])
		{
			if (mini->env[i]
				&& !ft_strncmp(mini->env[i], str[j], ft_strlen(str[j])))
			{
				count++;
				i++;
				j = 0;
			}
			else
				j++;
		}
		if (mini->env[i] != NULL)
			i++;
		j = 0;
	}
	return (count);
}

void	find_match(char **str, char **envi, int *control, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (!ft_strncmp(envi[(*i)], str[j], ft_strlen(str[j])))
		{
			(*i)++;
			j = 0;
			(*control) = 1;
			break ;
		}
		j++;
	}
}

void	to_make_it_shorter(t_mini *mini, char **valid, int *k)
{
	valid[(*k)] = NULL;
	(*k) = 0;
	cmp_env(valid, mini->env, mini, count_unsets(valid, mini, 0));
}
