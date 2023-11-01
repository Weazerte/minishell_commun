/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:09:35 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:54:49 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(const char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	start = 0;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	end = ft_strlen((char *)s1);
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	str = (char *)malloc(((end - start) + 1) * sizeof(*s1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

// int	main()
// {
// 	char	s[] = "   xxxtripouille";
// 	char	set[] = " x";
// 	printf("%s\n", ft_strtrim(s, set));
// 	return (0);
// }
