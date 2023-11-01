/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:53:42 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:54:09 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (i < (size -1) && src[i])
		{
			dst[i] = src[i];
			++i;
		}
	dst[i] = '\0';
	}
	while (src[i])
		++i;
	return (i);
}

// int	main()
// {
// 	char	*dest;
// 	dest = malloc(sizeof(char) * 15);
// 	printf("%ld\n", ft_strlcpy(dest, "lorem ipsum", 3));
// 	return (0);
// }