#include "../minishell.h"

int	command_list_count(t_mini *mini)
{
	int	i;
	t_mini *temp;

	i = 0;
	temp = mini;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_free_dp(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free (str[i]);
			str[i] = NULL;
			i++;
		}
		free (str);
		str = NULL;
	}
}