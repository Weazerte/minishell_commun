/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:08:07 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:46 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i] != '\0')
		i++;
	str = malloc(i * sizeof(char) + 1);
	if (str != NULL)
	{
		i = 0;
		while (src[i] != '\0')
		{
			str[i] = src[i];
			i++;
		}
		str[i] = '\0';
	}
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
