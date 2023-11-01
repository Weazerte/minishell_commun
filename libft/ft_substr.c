/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:56:55 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:29:08 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(char **copy, char const *s, unsigned int start,
	size_t len)
{
	size_t	min;

	if (len < ft_strlen((char *)s + start))
		min = len;
	else
		min = ft_strlen((char *)s + start);
	*copy = ft_calloc(min + 1, sizeof(**copy));
	return (min);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	i;

	if (start > ft_strlen((char *)s))
	{
		return (ft_calloc(1, 1));
	}
	i = 0;
	len = ft_min(&copy, s, start, len);
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = ((char *)s)[start];
		++start;
		++i;
	}
	copy[i] = '\0';
	return (copy);
}
//int	main()
//{
//	char	s[] = "lorem ipsum dolor sit amet";
//	printf("%s\n", ft_substr(s, 400, 20));
//	return (0);
//}
