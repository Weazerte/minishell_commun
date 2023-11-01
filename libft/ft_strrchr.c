/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:42:35 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:54:44 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (const char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// int	main()
// {
// 	char	test[] = "tripouille";
// 	char	test1[] = "tripouille";
// 	printf("%s\n", ft_strrchr(test, 't' + 256));
// 	printf("%s\n", strrchr(test1, 't' + 256));
// 	return (0);
// }