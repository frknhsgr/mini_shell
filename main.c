#include "minishell.h"

int	global_exit;

void utils_struct_init(t_utils *t, char *arg)
{
	if (arg[0])
	{
		t->i_c = heredoc_count(arg, 0, 0, 0);
		t->h_c = heredoc_count(arg, 0, 0, HEREDOC);
		t->o_c = append_count(arg, 0, 0, 0);
		t->a_c = append_count(arg, 0, 0, APPEND);
	}
	t->c = 0;
	t->k = 0;
	t->j = 0;
	t->dq = 0;
	t->sq = 0;
}

void init_mini_struct(t_mini *mini)
{
	mini->cmd = NULL;
	mini->flag_arg = NULL;
	mini->output = NULL;
	mini->append = NULL;
	mini->heredoc = NULL;
	mini->input = NULL;
	mini->next = NULL;
	mini->status = NONE;
}

int main(int ac, char **av)
{
	char    **args;
    char    *temp;
	char	*temp1;
    t_mini  mini;

	if (ac != 1)
		return(printf("Error: Invalid Argument Count!\n"));
	(void)av;
	global_exit = 0;
    take_env(&mini);
    while(1)
    {
		init_mini_struct(&mini);
        temp = readline("minishell> ");
		if (!temp)
		{
			printf("exit\n");
			exit(0);
		}
        add_history(temp);
		if (pp_counter(temp, 0, 0) == -1)
		{
			printf("Quote!\n");
			free(temp);
			continue;
		}
        temp1 = ft_strtrim(temp, " \t");
        free (temp);
        args = mm_split(temp1);
        read_args(&mini, args);
		if (mini.cmd != NULL)
			read_and_exec(&mini, command_list_count(&mini));
    }
}
