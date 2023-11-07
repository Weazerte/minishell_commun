/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:25:22 by mderkaou          #+#    #+#             */
/*   Updated: 2023/11/07 16:48:20 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	exec_with_args(t_cmds *data_exec, int infile, int outfile)
{
	char	**args;
	char	*path;
	int		status;

	status = 0;
	args = ft_split(data_exec->cmd, -7);
	path = ft_path_bin(args[0], data_exec->lst_env);
	if (!path || !args)
	{
		if (args)
			free_tab(args);
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		exit(ERROR);
	}
	dup_and_close(infile, outfile);
	status = execve(path, args, data_exec->env);
	exit(status);
}

void	exec_without_args(t_cmds *data_exec, int infile, int outfile)
{
	char	*path;
	char	*arr[2];
	int	status;

	path = ft_path_bin(data_exec->cmd, data_exec->lst_env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		exit(EXIT_FAILURE);
	}
	arr[0] = path;
	arr[1] = NULL;
	dup_and_close(infile, outfile);		
	status = execve(path, arr, data_exec->env);
	free(path);
	exit(status);
}
