/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:45:13 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:06 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	i = 0;
	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	while (i < n)
	{
		if (tmps1[i] != tmps2[i])
			return (tmps1[i] - tmps2[i]);
		i++;
	}
	return (0);
}

// int	main()
// {
// 	char	s1[] = "t\200";
// 	char	s2[] = "t\0";
// 	printf("%d\n", ft_memcmp(s1, s2, 2));
// 	printf("%d\n", memcmp(s1, s2, 2));
// 	return (0);
// }