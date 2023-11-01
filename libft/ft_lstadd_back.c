/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:45:26 by eaubry            #+#    #+#             */
/*   Updated: 2022/11/21 11:39:51 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nextlst;

	if (lst == NULL || new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		nextlst = ft_lstlast(*lst);
		nextlst->next = new;
	}
}
