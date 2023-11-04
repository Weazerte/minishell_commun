/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:25:17 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/04 18:37:09 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	cpy(char *dst, char const *src, int n)
{
	while (n--)
		*dst++ = *src++;
	*dst++ = '/';
	*dst = '\0';
}

static int	allocate(char const *s, char **list, int word_length, int index)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (word_length + 1));
	if (!word)
	{
		while (index >= 0)
			free(list[index--]);
		free(list);
		return (0);
	}
	cpy(word, (s - word_length), word_length);
	list[index++] = word;
	return (1);
}

static int	create_word(char const *s, char c, char **list, int words)
{
	int	word_length;
	int	index;

	index = 0;
	while (*s != '\0')
	{
		word_length = 0;
		if (*s != c)
		{
			while (index != words)
			{
				if (*s == c || *s == '\0')
				{
					if (!allocate(s, list, word_length, index))
						return (0);
					index++;
					break ;
				}
				word_length++;
				s++;
			}
		}
		s++;
	}
	return (index);
}

static int	count_words(char const *str, char c)
{
	int	words;

	words = 0;
	while (*str)
	{
		if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
			words++;
		str++;
	}
	return (words);
}

char	**ft_split_dos(char *s, char c, char *exe)
{
	int		words;
	char	**list;
	int		index;
	char	**tab;

	if (s == 0 || !s)
		return (0);
	words = count_words(s, c);
	list = malloc(sizeof(char *) * (words + 1));
	tab = malloc(sizeof(char *) * (words + 1));
	if (!list || !tab)
		return (NULL);
	index = create_word(s, c, list, words);
	if (!list)
		return (NULL);
	list[index] = NULL;
	index = -1;
	while (list[++index])
		tab[index] = ft_strjoin(list[index], exe);
	tab[index] = 0;
	free_tab(list);
	return (tab);
}
