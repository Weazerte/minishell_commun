#include "minishell_parse.h"

void	find_nbcmd(char *str)
{
	char *tmp;
	int i;

	tmp = check_quotes(str);
	i = 0;
	while(tmp[i])
	{
		if(tmp[i++] == '|')
		nbcmd += 1;
	}
	return (nbcmd);
}