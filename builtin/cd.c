/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:48:10 by weaz              #+#    #+#             */
/*   Updated: 2023/11/08 23:35:39 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	p_error(char **args)
{
	ft_putinfd("cd: ", 2);
	if (args[2])
		ft_putinfd("string not in pwd: ", 2);
	else
	{
		ft_putinfd(strerror(errno), 2);
		ft_putinfd(": ", 2);
	}
	ft_putinfd_n(args[1], 2);
}

static char	*get_env_path(t_env *lst_env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (lst_env && lst_env->next != NULL)
	{
		if (ft_strncmp(lst_env->env_line, var, len) == 0)
		{
			s_alloc = ft_strlen(lst_env->env_line) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			i = 0;
			j = 0;
			while (lst_env->env_line[i++])
				if (i > (int)len)
					oldpwd[j++] = lst_env->env_line[i];
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		lst_env = lst_env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *lst_env)
{
	char	cwd[300];
	char	*oldpwd;

	if (getcwd(cwd, 300) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (is_already_in_env(lst_env, oldpwd) == 0)
		env_add(oldpwd, lst_env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

static int	go2path(int option, t_env *lst_env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(lst_env);
		env_path = get_env_path(lst_env, "HOME", 4);
		if (!env_path)
			ft_putinfd_n("minishell : cd: HOME not set", STDERR);
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1)
	{
		env_path = get_env_path(lst_env, "OLDPWD", 6);
		if (!env_path)
			ft_putinfd_n("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (ERROR);
		update_oldpwd(lst_env);
	}
	ret = chdir(env_path);
	ft_putinfd_n(env_path, 1);
	ft_memdel(env_path);
	return (ret);
}

int	cd_builtin(char **args, t_env *lst_env)
{
	int	cd_ret;

	cd_ret = 0;
	if (!args[1])
		exit(go2path(0, lst_env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go2path(1, lst_env);
	else
	{
		update_oldpwd(lst_env);
		cd_ret = chdir(args[1]);
		if (cd_ret != 0)
			p_error(args);
	}
	return (SUCCESS);
}
