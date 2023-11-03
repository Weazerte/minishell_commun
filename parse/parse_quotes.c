/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:08 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/03 22:00:15 by mapierre         ###   ########.fr       */
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
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
	return (str);
}
