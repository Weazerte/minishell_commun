/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:16:22 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/18 19:21:32 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_calloc_str(size_t size)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

static int	get_size_str(long long int n)
{
	long long int	i;

	i = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*fill_str(char *str, long long int n, int len)
{
	int		start;

	str[len] = '\0';
	len = len - 1;
	if (n < 0)
	{
		n = n * -1;
		start = 1;
		str[0] = '-';
	}
	else
		start = 0;
	while (len >= start)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	long long int	nbr;

	nbr = n;
	len = get_size_str(nbr);
	if (nbr < 0)
		len = len + 1;
	str = ft_calloc_str(len);
	if (!str)
		return (NULL);
	str = fill_str(str, nbr, len);
	return (str);
}

// int	main()
// {
// 	printf("%s\n", ft_itoa(2147483647));
// 	return (0);
// }