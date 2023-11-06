/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:54:40 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:40 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_inside_sig(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	here_sig(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
