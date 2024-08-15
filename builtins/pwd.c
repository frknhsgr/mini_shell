#include "../minishell.h"

void    pwd()
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);
    g_global_exit = 0;
}