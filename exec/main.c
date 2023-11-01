/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:03:20 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/01 15:19:20 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	one_pipe(t_cmds *data_exec)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		//si plusieur args
		if (is_a_builtin(data_exec->cmd) == 0)
			exec_with_builtin(data_exec);
		else if ((ft_verif_space(data_exec->cmd) == 1))
			exec_with_args(data_exec, data_exec->infile,
					data_exec->outfile);
		else
			exec_without_args(data_exec, data_exec->infile,
					data_exec->outfile);
	}
    waitpid(pid, NULL, 0);
}

void	exec(t_cmds **data_exec)
{
	printf("cmd exec : %s\n", (*data_exec)[0].cmd);
    if ((*data_exec)->data.ncmd == 1)
    	one_pipe(*data_exec);
    else
    	make_all_exec(*data_exec);
}

//checker les strdup (leak)
char **ft_env_cpy(char **env)
{
	int	i;
	char **cpy;

	i = 0;
	while (env[i])
	{
		i++;
	}
	cpy = malloc(sizeof(char *) * (i + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while(env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

int	main_exec(int ac, char **av, char **env)
{
	t_cmds *data_exec;

	int	i = 0;
	int	j = 0;
	data_exec = malloc(sizeof(t_cmds) * (ac - 1));
	env_init(&data_exec->lst_env, env);
	data_exec->env = ft_env_cpy(env);
	data_exec->data.ncmd = (ac - 1);
	data_exec->infile = 1;
	data_exec->outfile = 0;
	while (++i < ac)
	{
		data_exec[j].cmd = ft_strdup(av[i]);
		printf("cmd main : %s\n", data_exec[i].cmd);
		j++;
	}
	// secret_env_init(data_exec.data, env);
	// data_exec.secret_lst_env = &secret_env;
	// if (data->ncmd == 1)
	exec(&data_exec);
	// while (data_exec.lst_env->next)
	// {
	// 	printf("%s\n", data_exec.lst_env->env_line);
	// 	data_exec.lst_env = data_exec.lst_env->next;
	// }
    // else
    // 	make_all_exec(data_exec, data);
	// ft_free_tabx2(data_exec->env);
	// ft_free_lst(data_exec->lst_env);
	// free(data_exec->cmd);
	return (0);
	// readline();
	//pars
	// exec(data_exec, data, env)
}
