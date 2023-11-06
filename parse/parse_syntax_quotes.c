/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:20:58 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:40 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				if (c == '\'')
					str[i] *= -1;
				i++;
			}
			if (!str[i])
				return (free(str), NULL);
		}
		i++;
	}
	return (str);
}

char	*ft_positive(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < -7)
			str[i] *= -1;
		i++;
	}
	return (str);
}

int	operator_parse(char *str, char op)
{
	char	*tmp;

	if (!str)
		return (0);
	tmp = str;
	while (*tmp && is_space(*tmp))
		tmp++;
	if (!*tmp)
		return (syntax_error(0));
	if (op == '|' && *tmp == '|')
		return (syntax_error(op));
	if (is_redirection(op) && is_operator(*tmp) && tmp - str)
		return (syntax_error(op));
	if (is_redirection(op) && is_operator(*tmp) && op != *tmp)
		return (syntax_error(op));
	if (is_redirection(op) && is_redirection(*tmp) && op == *tmp)
		if (is_operator(tmp[1]))
			return (syntax_error(op));
	if (is_redirection(*tmp))
		return (operator_parse(tmp + 1, *tmp));
	return (1);
}

int	syntax_error(char c)
{
	if (is_operator(c))
		printf ("bash: syntax error near unexpected token '%c'\n", c);
	else
		printf ("bash: syntax error near unexpected token 'newline'\n");
	return (0);
}

int	syntax_parse(char *str)
{
	int	is_start;

	if (!str)
		return (0);
	is_start = 1;
	while (*str)
	{
		if (!is_operator(*str) && !is_space(*str) && is_start)
			is_start = 0;
		if (is_operator(*str))
		{
			if (is_start && *str == '|')
				return (syntax_error(*str));
			if (!operator_parse(str + 1, *str))
				return (0);
		}
		if (str && *str)
			str++;
	}
	return (1);
}
