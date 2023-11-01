#include "../inc/minishell.h"

char *check_quotes(char *str)
{
	int	i;
	int	j;
	char c;

	i = 0;
	j = 0;

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
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*ft_positive(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
	return (str);
}