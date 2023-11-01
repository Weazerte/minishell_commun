#include "../inc/minishell.h"

size_t	find_pos_dollar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_var_name(char *str, int i)
{
	char *var;
	int count;
	int	j;

	j = 0;
	count = i;
	if (str[i] == '?')
	{
		var = malloc(2);
		if(!var)
			return (NULL);
		var[j++] = '0' + DQM;
		var[j] = '\0';
		return (var);
		//dqm est un int defini dans le .h , a remplacer par lexit status recu par lexec
	}
	//rajouter que si le premier caractere apres $ est un digit alors cest faux;checker bash(tant que cest des numeros alors ca ne compte pas)
	while(is_alpha(str[i]) || is_digit(str[i]) || is_space(str[i]))
		i++;
	var = malloc(sizeof(char) * (i - count) + 1);
	if (!var)
		return(NULL);                 
	while (count < i)
		var[j++] = str[count++];
	var[j] = '\0';
	return (var);
}

char *build_expended_line(char *before, char *value, char *after)
{
	size_t i;
	char *expanded;

	if (value == NULL)
		value = "";
	i = (ft_strlen(before) + ft_strlen(value) + ft_strlen(after));
	expanded = malloc(sizeof(char) * (i + 1));
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	ft_strlcat(expanded, before, ft_strlen(before) + 1);
	ft_strlcat(expanded, value, ft_strlen(before) + ft_strlen(value) + 1);
	ft_strlcat(expanded, after, i + 1);
	return (expanded);
}

char *split_env(char *str)
{
	size_t dollar_pos;
	char *before;
	char *to_expand;
	char *after;
	char *expanded;

	dollar_pos = find_pos_dollar(str);
	//if (dollar_pos == -1)
	//	return(NULL);
	before = ft_strndup(str, dollar_pos);
	to_expand = find_var_name(str, dollar_pos+1);
	after = ft_strndup(&str[dollar_pos + 1 + ft_strlen(to_expand)],
			ft_strlen(str));
	if (str[dollar_pos + 1] == '?')
		expanded = build_expended_line(before, to_expand, after);
	else
		expanded = build_expended_line(before, getenv(to_expand), after);
	printf("%s|\n", expanded);
	return (NULL);
}
	
	
