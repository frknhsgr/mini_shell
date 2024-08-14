#include "../minishell.h"

void	child_procces(t_mini *mini, char **command, int i)
{
	mini->pid = fork();
    if (mini->pid == 0)
    {
		ft_signal_regulator(CHILD_P);
		onecommand_output_input_regulator(mini, i, 0, 0);
		check_builtin_status(mini);
		if (mini->status != BUILTIN)
        	run_cmd(mini, command);
        else
            check_builtin(mini);
        exit(0);
    }
    return ;
}


void wait_child(t_mini *cmd)
{
    t_mini *temp;

    temp = cmd;
    while (temp)
    {
        waitpid(temp->pid, 0, 0);
        temp = temp->next;
    }
}