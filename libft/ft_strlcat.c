/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:53:01 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:53:57 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;

	src_length = ft_strlen(src);
	dest_length = ft_strlen(dst);
	i = 0;
	if (dest_length < size - 1 && size > 0)
	{
		while (src[i] && (dest_length + i) < (size - 1))
		{
			dst[dest_length + i] = src[i];
			i++;
		}
		dst[dest_length + i] = 0;
	}
	if (dest_length >= size)
		dest_length = size;
	return (dest_length + src_length);
}

// int main (void)
// {
//     char    str[] = "rrrrrrrrrrrrrrr";
//     int    i;

//     i = ft_strlcat(str,"lorem ipsum dolor sit amet", 5);
//     printf("%s", str);
//     printf("%d", i);
//     return (0);
// }