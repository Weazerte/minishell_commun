/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:08:07 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/08 20:15:05 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int main(void)
// {
// 	char	*str;
// 	char	*streal;
// 	char	*src = "abcdesfsdgsdgsdgsgsdsddgsdgsfs";

// 	streal = strdup(src);
// 	str = ft_strdup(src);
// 	printf("%c %c\n", streal[0], streal[70]);
// 	printf("%c %c", str[0], str[70]);
// }
