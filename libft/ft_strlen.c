/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:12:46 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/01 12:52:11 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (str == 0)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	int	i;

// 	i = ft_strlen(NULL);
// 	printf("%d",i);
// 	return (0);
// }
