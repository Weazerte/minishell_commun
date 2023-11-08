/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:38:47 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/08 23:44:14 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	env_add(char *line, t_env *lst_env)
{
	t_env	*new;
	t_env	*tmp;

	if (lst_env && lst_env->env_line == NULL)
	{
		lst_env->env_line = ft_strdup(line);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->env_line = ft_strdup(line);
	while (lst_env && lst_env->next && lst_env->next->next)
		lst_env = lst_env->next;
	tmp = lst_env->next;
	lst_env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

char	*get_name_in_env(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_already_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_name_in_env(var_name, args);
	while (env && env->next)
	{
		get_name_in_env(env_name, env->env_line);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->env_line);
			env->env_line = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	export_builtin(char **args, t_env *lst_env)
{
	int	new_env;
	int	error_ret;

	new_env = 0;
	error_ret = is_valid_env(args[1]);
	if (args[1][0] == '=')
		error_ret = -3;
	if (error_ret <= 0)
		return (print_error(error_ret, args[1]), ERROR);
	else
		if (is_already_in_env(lst_env, args[1]) == 1)
			new_env = 1;
	if (new_env == 0)
	{
		if (error_ret == 1)
			env_add(args[1], lst_env);
	}
	return(SUCCESS);
}
