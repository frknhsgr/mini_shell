/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhosgor <fhosgor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:24:12 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 14:31:11 by fhosgor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_check(char **keep, int *i)
{
	if (keep[0][0] == '-')
	{
		printf("unset: invalid option\n");
		g_global_exit = 2;
		return (0);
	}
	if ((keep[(*i)][0] >= '0' && keep[(*i)][0] <= '9'))
	{
		printf("unset: '%s': not a valid identifier\n", keep[(*i)]);
		(*i)++;
		g_global_exit = 1;
		return (1);
	}
	return (-1);
}

void	while_start_unset(t_mini *mini, char **keep, char **valid, int *k)
{
	int	s;
	int	i;
	int	control;

	i = 0;
	control = 0;
	while (keep[i])
	{
		s = unset_check(keep, &i);
		if (s == 0)
			return ;
		else if (s == 1)
			continue ;
		unset_typo(mini, keep, &i, &control);
		if (export_unset_control(&control) == 1)
			continue ;
		else
			valid[(*k)++] = ft_strjoin(keep[i++], "=");
	}
}

void	cmp_env(char **str, char **envi, t_mini *mini, int cnt)
{
	int	i;
	int	e;
	int	j;
	int	control;

	if (!cnt)
		return ;
	mini->env = malloc(sizeof(char *) * (count_environ(mini->env) - cnt + 1));
	i = 0;
	e = 0;
	control = 0;
	while (envi[i])
	{
		find_match(str, envi, &control, &i);
		if (control == 0)
		{
			mini->env[e++] = ft_strdup(envi[i]);
			i++;
			j = 0;
		}
		else
			control = 0;
	}
	mini->env[e] = NULL;
	free_env(envi);
}

void	ft_start_unset(t_mini *mini)
{
	int		i;
	int		k;
	char	**keep;
	char	**valid;

	i = 0;
	k = 0;
	keep = mm_split(ft_strdup(mini->flag_arg), ' ');
	valid = NULL;
	valid = malloc(sizeof(char *) * (count_environ(keep)) + 1);
	while_start_unset(mini, keep, valid, &k);
	to_make_it_shorter(mini, valid, &k);
	free_env(keep);
	free_env(valid);
}

void	ft_unset(t_mini *mini)
{
	if (mini->flag_arg && mini->flag_arg[0])
		ft_start_unset(mini);
}
