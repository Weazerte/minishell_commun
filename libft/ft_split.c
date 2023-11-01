/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:34:03 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:35 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issep(char cmp, char c)
{
	if (c == 0)
	{
		if (c == cmp)
			return (1);
		return (0);
	}
	else
	{
		if (c == cmp || cmp == '\0')
			return (1);
		return (0);
	}
}

static int	ft_size_word(char const *str, unsigned char c)
{
	int	i;
	int	hword;

	i = 0;
	hword = 0;
	while (ft_issep(str[i], c) == 1)
		i++;
	while (ft_issep(str[i], c) == 0)
	{
		i++;
		hword++;
	}
	return (hword);
}

static int	ft_str(char **tab, int n, char c, char const *str)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = ft_size_word(str, c);
	tab[n] = malloc((size + 1) * sizeof(char));
	if (!tab[n])
		return (0);
	while (ft_issep(str[i], c) == 1)
		i++;
	j = 0;
	while (ft_issep(str[i], c) == 0)
	{
		tab[n][j] = str[i];
		i++;
		j++;
	}
	tab[n][j] = '\0';
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		n;
	int		sizeall;

	sizeall = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c) && (s[i + 1] == c || s[i + 1] == '\0'))
			sizeall++;
		i++;
	}
	tab = malloc((sizeall + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	n = 0;
	while (n < sizeall)
	{
		i += ft_str(tab, n, (unsigned char)c, &s[i]);
		n++;
	}
	tab[n] = 0;
	return (tab);
}

// int    main()
// {
//     // int        index;
//     char	**split;
//     split = ft_split("tripouille", 0);
// 	printf("%s\n", split[0]);
//     // index = 0;
//     // while (split[index] != 0)
//     // {
//     //     printf("%s\n", split[index]);
//     //     index++;
//     // }
//     return (0);
// }