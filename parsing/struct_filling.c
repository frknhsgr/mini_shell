#include "../minishell.h"

void take_heredoc(t_utils *t, t_mini *cmd, char *arg)
{
	static int	i;

	t->c++;
	while (arg[t->c] && arg[t->c] == ' ') 
		t->c++;
	t->k = t->c;
	while (arg[t->c])
	{
		quote_check(arg[t->c], &t->sq, &t->dq);
		if ((arg[t->c] == ' ' && t->sq % 2 == 0 && t->dq % 2 == 0) || (ft_strchr("<>", arg[t->c]) && t->sq % 2 == 0 && t->dq % 2 == 0))
			break ;
		t->c++;
	}
	if (i < t->h_c)
	{
	 	cmd->heredoc[i] = ft_substr(arg, t->k, t->c - t->k);
		i++;
	}
	if (i == t->h_c)
	{
		cmd->heredoc[i] = NULL;
		i = 0;
	}
	heredoc_status_regulator(cmd, HEREDOC);
}


void	take_input(t_utils *t, t_mini *cmd, char *arg)
{
	static int	i;

	while (arg[t->c] && arg[t->c] == ' ') 
		t->c++;
	t->k = t->c;
	while (arg[t->c])
	{
		quote_check(arg[t->c], &t->sq, &t->dq);
		if ((arg[t->c] == ' ' && t->sq % 2 == 0 && t->dq % 2 == 0) || (ft_strchr("<>", arg[t->c]) && t->sq % 2 == 0 && t->dq % 2 == 0))
			break ;
		t->c++;
	}
	if (i < t->i_c)
	{
	 	cmd->input[i] = ft_substr(arg, t->k, t->c - t->k);
		i++;
	}
	if (i == t->i_c)
	{
		cmd->input[i] = NULL;
		i = 0;
	}
	heredoc_status_regulator(cmd, 0);
}

void	take_append(t_utils *t, t_mini *cmd, char *arg)
{
	static int	i;

	t->c++;
	while (arg[t->c] && arg[t->c] == ' ') 
		t->c++;
	t->k = t->c;
	while (arg[t->c])
	{
		quote_check(arg[t->c], &t->sq, &t->dq);
		if ((arg[t->c] == ' ' && t->sq % 2 == 0 && t->dq % 2 == 0) || (ft_strchr("<>", arg[t->c]) && t->sq % 2 == 0 && t->dq % 2 == 0))
			break ;
		t->c++;
	}
	if (i < t->a_c)
	{
	 	cmd->append[i] = ft_substr(arg, t->k, t->c - t->k);
		i++;
	}
	if (i == t->a_c)
	{
		cmd->append[i] = NULL;
		i = 0;
	}
	append_status_regulator(cmd, APPEND);
}

void	take_output(t_utils *t, t_mini *cmd, char *arg)
{
	static int	i;

	while (arg[t->c] && arg[t->c] == ' ') 
		t->c++;
	t->k = t->c;
	while (arg[t->c])
	{
		quote_check(arg[t->c], &t->sq, &t->dq);
		if ((arg[t->c] == ' ' && t->sq % 2 == 0 && t->dq % 2 == 0) || (ft_strchr("<>", arg[t->c]) && t->sq % 2 == 0 && t->dq % 2 == 0))
			break ;
		t->c++;
	}
	if (i < t->o_c)
	{
	 	cmd->output[i] = ft_substr(arg, t->k, t->c - t->k);
		i++;
	}
	if (i == t->o_c)
	{
		cmd->output[i] = NULL;
		i = 0;
	}
	append_status_regulator(cmd, 0);
}


void filling_struct(t_mini *cmd, t_utils *t, char *arg)
{
	char	*temp1;
	char	*temp2;

	while (arg[t->c])
	{
		quote_check(arg[t->c], &t->sq, &t->dq);
		if (arg[t->c] == '<' && t->sq % 2 == 0 && t->dq % 2 == 0)
		{
			if (arg[++t->c] == '<')
				take_heredoc(t, cmd, arg);
			else
				take_input(t, cmd, arg);
		}
		else if (arg[t->c] == '>' && t->sq % 2 == 0 && t->dq % 2 == 0)
		{
			if (arg[++t->c] == '>')
				take_append(t, cmd, arg);
			else
				take_output(t, cmd, arg);
		}
		else
		{
			if (cmd->cmd == NULL)
			{
				while (arg[t->c] && arg[t->c] == ' ')
					t->c++;
				if (t->c != 0)
					quote_check(arg[t->c], &t->sq, &t->dq);
				t->k = t->c;
				while (arg[t->c])
				{
					if ((arg[t->c] == ' ' && t->sq % 2 == 0 && t->dq % 2 == 0)
					|| (ft_strchr("<>", arg[t->c]) && t->sq % 2 == 0 && t->dq % 2 == 0))
						break ;
					t->c++;
					quote_check(arg[t->c], &t->sq, &t->dq);
				}
				cmd->cmd = ft_substr(arg,t->k, t->c - t->k);
			}
			else if (cmd->flag_arg == NULL || cmd->flag_arg)
			{
				while (arg[t->c] && arg[t->c] == ' ')
					t->c++;
				t->k = t->c;
				while (arg[t->c])
				{
					quote_check(arg[t->c], &t->sq, &t->dq);
					if (ft_strchr("<>", arg[t->c]) && t->sq % 2 == 0 && t->dq % 2 == 0)
						break ;
					t->c++;
				}
				if (cmd->flag_arg == NULL)
					cmd->flag_arg = ft_substr(arg,t->k, t->c - t->k);
				else if (cmd->flag_arg)
				{
					temp1 = cmd->flag_arg;
					temp2 = ft_substr(arg,t->k, t->c - t->k);
					cmd->flag_arg = ft_strjoin (temp1, temp2);
					free (temp1);
					free (temp2);
				}
			}
			else
				t->c++;
		}
		
	} 
}

void print_cmd(t_mini *cmd)
{
	t_mini *temp;

	temp = cmd;
	while (cmd)
	{
		if (cmd->cmd)
			printf("CMD: %s\n",cmd->cmd);
		if (cmd->flag_arg)
			printf("FLAG_ARG: %s\n",cmd->flag_arg);
		for (int x = 0; cmd->output[x];x++)
			printf("OUTPUT: %s\n",cmd->output[x]);
		for (int x = 0; cmd->input[x];x++)
			printf("INPUT: %s\n",cmd->input[x]);
		for (int x = 0; cmd->heredoc[x];x++)
			printf("HEREDOC: %s\n",cmd->heredoc[x]);
		for (int x = 0; cmd->append[x];x++)
			printf("APPEND: %s\n",cmd->append[x]);
		printf("status = %d\n", cmd->status);
		printf("----------------\n");
		cmd = cmd->next;
	}
	cmd = temp;
}

void	status_regulator(t_mini * mini)
{
	if (mini->status == HEREDOC)
		mini->status = PIPEHEREDOC;
	else if (mini->status == APPEND)
		mini->status = PIPEAPPEND;
	else if (mini->status == HEREDOCAPPEND)
		mini->status = PIPEHEREDOCAPPEND;
	else if (mini->status == NONE)
		mini->status = PIPE;
}

void	append_status_regulator(t_mini *mini, int type)
{
	if (mini->status == NONE && type == APPEND)
		mini->status = APPEND;
	else if (mini->status == HEREDOC && type == APPEND)
		mini->status = HEREDOCAPPEND;
	else if (mini->status == APPEND && type == 0)
		mini->status = NONE;
	else if (mini->status == HEREDOCAPPEND && type == 0)
		mini->status = HEREDOC;
}

void	heredoc_status_regulator(t_mini *mini, int type)
{
	if (mini->status == NONE && type == HEREDOC)
		mini->status = HEREDOC;
	else if (mini->status == APPEND && type == HEREDOC)
		mini->status = HEREDOCAPPEND;
	else if (mini->status == HEREDOC && type == 0)
		mini->status = NONE;
	else if (mini->status == HEREDOCAPPEND && type == 0)
		mini->status = APPEND;
	
}

void	read_args(t_mini *cmd, char **arg)
{
	t_utils t;
	t_mini *temp;
	int		i;

	i = 0;
	temp = cmd;
	while (arg[i])
	{
		utils_struct_init(&t, arg[i]);
		if (arg[i] && i > 0)
		{
			status_regulator(cmd);
			cmd->next = malloc(sizeof(t_mini));
			cmd->next->env = cmd->env;
			cmd = cmd->next;
			init_mini_struct(cmd);
			cmd->next = NULL;
		}
		ft_allcation_for_struct(cmd, &t);
		filling_struct(cmd,&t,arg[i]);
		i++;
	}
	cmd = temp;
	//print_cmd(cmd);
}