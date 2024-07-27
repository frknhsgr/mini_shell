#include "../minishell.h"


void quote_check(char temp, int *squotes, int *dquotes)
{
	if(temp == 34 && *squotes % 2 == 0)
		(*dquotes)++;
	if(temp == 39 && *dquotes % 2 == 0)
		(*squotes)++;
}

int pp_counter(char *temp, int squotes, int dquotes)
{
	int i;
	int d;

	d= 0;
	i = -1;
	while(temp[++i] && (quote_check(temp[i], &squotes, &dquotes), 1))
		if (temp[i] == '|' && (dquotes % 2 == 0 && squotes % 2 == 0))
			d++;
	d++;
	if (squotes % 2 == 1 || dquotes % 2 == 1)
		return (-1);
	return (d);
}

void	sub(char *temp, int squotes, int dquotes, char ***ret)
{
	int	i;
	int j;
	int d;
	char *tmp;

	i = 0;
	j = 0;
	d = 0;
	while(temp[i] && (quote_check(temp[i], &squotes, &dquotes), 1))
	{
		if(temp[i] == '|' && (dquotes % 2 == 0 && squotes % 2 == 0))
		{
			tmp = ft_substr(temp, d, i - d);
			(*ret)[j] = ft_strtrim(tmp, " \t");
			
			free(tmp);
			j++;
			d = i + 1;
		}
		i++;
	}
	tmp = ft_substr(temp, d, i - d);
	(*ret)[j++] = ft_strtrim(tmp,  " \t");
	free(tmp);
	(*ret)[j] = NULL;
}

char    **mm_split(char *temp)
{
	char **ret;


	ret = malloc(sizeof(char *) * (pp_counter(temp, 0, 0) + 1));
	if(!ret)
	   return (NULL);
	sub(temp, 0, 0, &ret);
	free (temp);
	return (ret);
}
