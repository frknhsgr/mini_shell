#include "../minishell.h"

int	heredoc_count(char *str, int dq, int sq, int type)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		quote_check(str[i], &dq, &sq);
		if (str[i] == '<' && dq % 2 == 0 && sq % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] != '<' && type != HEREDOC)
				count++;
			else if (str[i + 1] && str[i + 1] == '<' && type == HEREDOC)
				count++;
			else if (str[i + 1] && str[i + 1] == '<' && type != HEREDOC)
				i++;
		}
		i++;
	}
	return (count);
}

int	append_count(char *str, int dq, int sq, int type)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		quote_check(str[i], &dq, &sq);
		if (str[i] == '>' && dq % 2 == 0 && sq % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] != '>' && type != APPEND)
				count++;
			else if (str[i + 1] && str[i + 1] == '>' && type == APPEND)
				count++;
			else if (str[i + 1] && str[i + 1] == '>' && type != APPEND)
				i++;
		}
		i++;
	}
	return (count);
}

void	ft_allcation_for_struct(t_mini *cmd, t_utils *t)
{
	cmd->append = malloc (sizeof(char *) * (t->a_c + 1));
	if (!cmd->append)
		return ;
	if (t->a_c == 0)
		cmd->append[0] = NULL;
	cmd->output = malloc (sizeof(char *) * (t->o_c + 1));
	if (!cmd->output)
		return ;
	if (t->o_c == 0)
		cmd->output[0] = NULL;
	cmd->heredoc = malloc (sizeof(char *) * (t->h_c + 1));
	if (!cmd->heredoc)
		return ;
	if (t->h_c == 0)
		cmd->heredoc[0] = NULL;
	cmd->input = malloc (sizeof(char *) * (t->i_c + 1));
	if (!cmd->input)
		return ;
	if (t->i_c == 0)
		cmd->input[0] = NULL;
}