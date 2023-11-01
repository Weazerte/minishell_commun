#include "minishell_parse.h"

char *check_quotes(char *line)
{
	int	i;
	int	j;
	char c;
	char *str;

	i = 0;
	j = 0;
	str = ft_strdup(line);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = 1;
			c = str[i];
			i++;
			while (str[i])
			{
				if (str[i] == c)
				{
					j = 0;
					break ;
				}
				else if (c == '\'')
                    str[i] *= -1;
                i++;
			}
		}
        i++;
	}
	if (j == 1)
		return (NULL);
	return (str);
}