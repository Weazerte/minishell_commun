/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:39:00 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:28:29 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	if (ft_strlen(s1) == 0 && ft_strlen(s2) == 0)
		return (0);
	tmp1 = ((unsigned char *)s1);
	tmp2 = ((unsigned char *)s2);
	while (i < n)
	{
		if (tmp1[i] != tmp2[i])
			return (tmp1[i] - tmp2[i]);
		else
			i++;
	}
	return (0);
}

// int	main()
// {
// 	printf("%d\n", ft_strncmp("test\200", "test\0", 6));
// 	printf("%d\n", strncmp("test\200", "test\0", 6));
// 	return (0);
// }