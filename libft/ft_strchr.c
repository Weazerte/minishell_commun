/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:33:36 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:41 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	t;

	i = 0;
	t = ((unsigned char)c);
	if (c == '\0')
	{
		while (s[i])
			i++;
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == t)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char	test[] = "tripouille";
// 	char	test1[] = "tripouille";
// 	printf("%s\n", ft_strchr(test, 't' + 256));
// 	printf("%s\n", strchr(test1, 't' + 256));
// 	return (0);
// }