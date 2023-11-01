/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:30:27 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:16 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, int n)
{
	char	*m;

	m = ((char *)s);
	while (n--)
	{
		*m = ((char)c);
		m++;
	}
	return (s);
}

// int	main()
// {
// 	void	*s;
// 	char	t[10];
// 	char	*test;
// 	char	*test1;

// 	s = t;
// 	test = ft_memset(s, 'f', sizeof(*t));
// 	test1 = memset(s, 'f', sizeof(*t));
// 	printf("%s\n", test);
// 	printf("%s\n", test1);
// 	return (0);
// }