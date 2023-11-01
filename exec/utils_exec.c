/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:16:30 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/01 14:04:30 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// builtin avec execve 

void	ft_make_thing(t_cmds *data_exec, int i, int read_pipe, int write_pipe)
{
	char	**str;
	char	*path;

	(void)i;
	// separer la commande
	str = ft_split(data_exec->cmd, ' ');
	path = ft_path_bin(str[0], data_exec->lst_env);
	if (!path || !str)
	{
		// si path est pas bon ou cmd pas bon return lign print error
		if (str)
			ft_free_tabx2(str);
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		ft_free_int(data_exec, -1);
		exit(EXIT_FAILURE);
	}
	if (write_pipe != 0 && write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	if (read_pipe != 1 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	execve(path, str, data_exec->env);
	ft_free_int(data_exec, -1);
	exit(-1);
}

void	ft_make_thing_two(t_cmds *data_exec, int i, int read_pipe, int write_pipe)
{
	char	*path;
	char	*arr[2];

	(void)i;
	path = ft_path_bin(data_exec->cmd, data_exec->lst_env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(data_exec->cmd);
		ft_free_int(data_exec, -1);
		exit(EXIT_FAILURE);
	}
	arr[0] = path;
	arr[1] = NULL;
		if (write_pipe != 1 && write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	if (read_pipe != 0 && read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	execve(path, arr, data_exec->env);
	ft_free_int(data_exec, -1);
	exit(-1);
}

void	ft_first_pipe(t_cmds *data_exec, int i)
{
	int	j;

	j = 0;
	//close les pipes pas utilises
	printf("cmd : %s\n", data_exec->cmd);
	if (data_exec->outfile != -1 && data_exec->outfile != 0)
		close(data_exec->outfile);
	close(data_exec->data.pipe[0][0]);
	while (++j < data_exec->data.ncmd)
		ft_close_fd(data_exec->data.pipe[j]);
	if (data_exec->infile == -1)
	{
		close(data_exec->data.pipe[0][1]);
		ft_free_int(data_exec, -1);
		exit(EXIT_FAILURE);
	}
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_make_thing(data_exec, i, data_exec->infile, data_exec->data.pipe[0][1]);
	else
		ft_make_thing_two(data_exec, i, data_exec->infile, data_exec->data.pipe[0][1]);
}

void	ft_inter_pipe(t_cmds *data_exec, int i)
{
	int	j;

	//close les pipes pas utilises
	if (data_exec->infile != -1 && data_exec->infile != 1)
		close(data_exec->infile);
	if (data_exec->outfile != -1 && data_exec->outfile != 0)
    	close(data_exec->outfile);
	close(data_exec->data.pipe[i][0]);
	close(data_exec->data.pipe[i - 1][1]);
	j = -1;
	while (++j < data_exec->data.ncmd)
		if (j != i && j != (i - 1))
			ft_close_fd(data_exec->data.pipe[j]);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_make_thing(data_exec, i, data_exec->data.pipe[i - 1][0], data_exec->data.pipe[i][1]);
	else
		ft_make_thing_two(data_exec, i, data_exec->data.pipe[i - 1][0], data_exec->data.pipe[i][1]);
}

void	ft_last_pipe(t_cmds *data_exec, int i)
{
	int	j;

	//close les pipes pas utilises
	close(data_exec->data.pipe[i - 1][1]);
	ft_close_fd(data_exec->data.pipe[i]);
	j = -1;
	while (++j < (i - 1))
		ft_close_fd(data_exec->data.pipe[j]);
	//gerer le probleme ou last commande a besoins de stdin au lieu du pipe
	if (data_exec->infile != 0)
	{
		close(data_exec->data.pipe[i - 1][0]);
		if ((ft_verif_space(data_exec->cmd) == 1))
			ft_make_thing(data_exec, i, data_exec->infile, data_exec->outfile);
		else
			ft_make_thing_two(data_exec, i, data_exec->infile, data_exec->outfile);
	}
	else
		close(data_exec->infile);
	if ((ft_verif_space(data_exec->cmd) == 1))
		ft_make_thing(data_exec, i, data_exec->data.pipe[i - 1][0], data_exec->outfile);
	else
		ft_make_thing_two(data_exec, i, data_exec->data.pipe[i - 1][0], data_exec->outfile);
}
