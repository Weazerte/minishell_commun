/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:09:27 by weaz              #+#    #+#             */
/*   Updated: 2023/10/31 16:40:38 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int env_builtin(t_env *lst_env)
{
    printf("%s\n", lst_env->env_line);
    while (lst_env && lst_env->next)
    {
        ft_putinfd(lst_env->env_line, 1);
        lst_env = lst_env->next;
    }
    if (lst_env)
        ft_putinfd(lst_env->env_line, 1);
    return (0);
}