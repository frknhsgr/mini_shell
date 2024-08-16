#include "../minishell.h"

void	check_flag(char *str, int *j, int *flag)
{
	while (str[*j] && str[*j] == 'n')
		j++;

}

void	check_echo_arg(char *str, int *i, int *j, int *flag)
{
	while (str[*i])
	{
		if (i == 0 && str[*i] == '-')
			check_flag(str, j, flag);
	}
}

void	ft_echo(t_mini *mini)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 1;
	flag = 0;
	if (mini->flag_arg && mini->flag_arg[0])
	{
		check_echo_arg(mini->flag_arg, &i, &j, &flag);
	}
	else
		printf("\n");
}