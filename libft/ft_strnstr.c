/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:02:35 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:54:38 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_equal(char *tmp, const char *little, size_t len, size_t i)
{
	size_t	j;

	j = 0;
	while (i < len && tmp[i] == little[j] && little[j])
	{
		j++;
		i++;
	}
	return (j);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*tmp;

	i = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	tmp = (char *)big;
	while (tmp[i] && i < len)
	{
		j = 0;
		if (tmp[i] == little[0])
			j = ft_equal(tmp, little, len, i);
		if (j == (ft_strlen(little)))
			return (tmp + i);
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	printf("%s\n", ft_strnstr("", "", -1));
// 	return (0);
// }