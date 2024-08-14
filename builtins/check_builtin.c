#include "../minishell.h"

char	*make_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	builtin_strcmp(char *s1, char *s2)
{
	if (check_same(s1, s2) == 0 || check_same(make_lower(s1), s2) == 0)
		return (0);
	return (1);
}

void	check_builtin(t_mini *mini)
{
	if (mini->cmd && check_same(mini->cmd, "cd") == 0)
		cd(mini, mini->flag_arg);
}

void	check_builtin_status(t_mini *mini)
{
	if (mini->cmd && check_same(mini->cmd, "exit") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && check_same(mini->cmd, "export") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && check_same(mini->cmd, "unset") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && check_same(mini->cmd, "cd") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && builtin_strcmp(mini->cmd, "env") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && builtin_strcmp(mini->cmd, "pwd") == 0)
		mini->status = BUILTIN;
	else if (mini->cmd && builtin_strcmp(mini->cmd, "echo") == 0)
		mini->status = BUILTIN;
}