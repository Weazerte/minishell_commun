/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:12:23 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:03 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	while (i < n)
	{
		if (tmp[i] == (char)c)
			return (&tmp[i]);
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	char s1[] = "qwrfcgeabn ioqarhboiapc";
// 	printf("%p\n", ft_memchr(s1, 99, 24));
// 	printf("%p\n", memchr(s1, 99, 24));
// 	return (0);
// }