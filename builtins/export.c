/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:24:07 by sgokcu            #+#    #+#             */
/*   Updated: 2024/09/09 16:40:14 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exp_control(t_mini *mini, char **keep, int *i, int control)
{
	if (keep[0][0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(keep[(0)], 2);
		ft_putstr_fd(": invalid option\n", 2);
		g_global_exit = 2;
		return (0);
	}
	if (((keep[(*i)][0] >= '0' && keep[(*i)][0] <= '9') \
	|| keep[(*i)][0] == '='))
		return (make_it_short(mini, keep, i), 1);
	if (!ft_strchr(keep[(*i)], '='))
	{
		exp_contains_equal(mini, keep, &(*i), &control);
		(*i)++;
		if (control == 1)
		{
			control = 0;
			(*i)--;
		}
		return (1);
	}
	return (-1);
}

void	exp_contains_equal(t_mini *mini, char **keep, int *i, int *control)
{
	int		sq;
	int		dq;
	int		j;

	dq = 0;
	sq = 0;
	j = 0;
	while (keep[(*i)] && keep[(*i)][j] && keep[(*i)][j] != '='
	&& (quote_check(keep[(*i)][j], &sq, &dq), 1))
	{
		if ((!(ft_isalnum(keep[(*i)][j])) && keep[(*i)][j] != '_')
		|| ((keep[(*i)][j] == 34 && sq % 2 != 0) || (keep[(*i)][j] == 39
		&& dq % 2 != 0)))
		{
			export_err_msg(delete_quotes(ft_strdup(keep[(*i)]), \
			mini, 0, 0), 0);
			(*i)++;
			(*control) = 1;
			g_global_exit = 1;
			break ;
		}
		j++;
	}
}

void	exp_putting(t_mini *mini, char **keep, int *i)
{
	char	*hold;

	hold = export_business(keep[(*i)], mini);
	if (does_env_have(hold, mini))
	{
		free(mini->env[does_env_have(hold, mini)]);
		mini->env[does_env_have(hold, mini)] = \
		delete_quotes(ft_strdup(keep[(*i)]), mini, 0, 0);
	}
	else
	{
		put_env(delete_quotes(ft_strdup(keep[(*i)]), mini, 0, 0), mini);
	}
	free(hold);
	(*i)++;
}

void	ft_start_exp(t_mini *mini)
{
	char	**keep;
	int		i;
	int		d;
	int		control;

	i = 0;
	control = 0;
	keep = mm_split(ft_strdup(mini->flag_arg), ' ');
	while (keep[i])
	{
		d = exp_control(mini, keep, &i, 0);
		if (d == 0)
		{
			free_env(keep);
			return ;
		}
		else if (d == 1)
			continue ;
		exp_contains_equal(mini, keep, &i, &control);
		if (export_unset_control(&control) == 1)
			continue ;
		else
			exp_putting(mini, keep, &i);
	}
	free_env(keep);
}

void	ft_export(t_mini *mini)
{
	if (mini->flag_arg && mini->flag_arg[0])
		ft_start_exp(mini);
	else
		ft_env(mini, 1);
}
