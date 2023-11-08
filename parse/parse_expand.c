/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:28:19 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/08 20:47:55 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_pos_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_var_name(char *str, int i)
{
	char	*var;
	int		count;
	int		j;

	j = 0;
	count = i;
	if (str[i] == '?')
		return (dollar_qm());
	while (is_digit(str[i]))
		i++;
	if (i == count)
	{
		while (is_alpha(str[i]) || is_digit(str[i]) || str[i] == '_')
			i++;
	}
	var = malloc(sizeof(char) * (i - count) + 1);
	if (!var)
		return (NULL);
	while (count < i)
		var[j++] = (str[count++]);
	var[j] = '\0';
	return (var);
}

char	*build_expanded_line(char *before, char *value, char *after)
{
	int		i;
	char	*expanded;
	unsigned long int		j;

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
	j = ft_strlen(before);
	while (expanded[j] && j < (ft_strlen(before) + ft_strlen(value)))
		expanded[j++] *= -1;
	return (expanded);
}

char	*split_env(char *str, int dollar_pos, t_env *backup_env)
{
	char	*before;
	char	*to_expand;
	char	*after;
	char	*expanded;

	before = ft_strndup(str, dollar_pos);
	to_expand = find_var_name(str, dollar_pos + 1);
	// printf("VAR_NAME = [%s]", to_expand);
	after = ft_strndup(&str[dollar_pos + 1 + ft_strlen(to_expand)],
			ft_strlen(str));
	if (str[dollar_pos + 1] == '?')
		expanded = build_expanded_line(before, to_expand, after);
	else
		expanded = build_expanded_line(before, ft_get_env(backup_env, to_expand), after);
	// printf("AFTER EXPAND = [%s]\n", expanded);
	free(before);
	free(to_expand);
	free(after);
	return (expanded);
}

char	*expand_all(char *str, t_env *backup_env)
{
	char	*result;
	int		dollar_pos;
	char	*temp;

	result = str;
	dollar_pos = find_pos_dollar(result);
	while (dollar_pos != -1)
	{
		temp = result;
		result = split_env(result, dollar_pos, backup_env);
		free(temp);
		dollar_pos = find_pos_dollar(result);
	}
	return (result);
}