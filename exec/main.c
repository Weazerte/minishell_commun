/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:03:20 by diavolo           #+#    #+#             */
/*   Updated: 2023/11/04 20:34:07 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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

int		one_pipe(t_cmds *data_exec)
{
	pid_t pid;
	int	v_ret;

	v_ret = 0;
	pid = fork();
	if (pid == 0)
	{
		//si plusieur args
		if (is_a_builtin(data_exec->cmd) == 0)
			v_ret = exec_with_builtin(data_exec);
		else if ((ft_verif_space(data_exec->cmd) == 1))
			exec_with_args(data_exec, data_exec->infile,
					data_exec->outfile);
		else
			exec_without_args(data_exec, data_exec->infile,
					data_exec->outfile);
	}
    waitpid(pid, NULL, 0);
	ft_free_one_ex(data_exec);
	return (v_ret);
}

int		exec(t_cmds **data_exec)
{
    if ((*data_exec)->ncmd == 1)
    	return (one_pipe(*data_exec));
    else
    	return (make_all_exec(*data_exec));
}

// int	main(int ac, char **av, char **env)
// {
// 	t_cmds *data_exec;
// 	int		ex = 0;
// 	int ret;

// 	if (ac == 2)
// 	{
// 		(void)ac;
// 		data_exec = malloc(sizeof(t_cmds) * (1));
// 		env_init(&data_exec->lst_env, env);
// 		// ft_print_lst(data_exec->lst_env);
// 		// printf("verif ::::: %s\n", data_exec->lst_env->env_line);
// 		data_exec->env = ft_env_cpy(env);
// 		data_exec->ncmd = 1;
// 		data_exec->infile = 0;
// 		data_exec->outfile = 1;
// 		data_exec->exit = ex;
// 		data_exec->cmd = ft_strdup(av[1]);
// 	}
// 	else
// 	{
// 		(void)ac;
// 		(void)av;
// 		data_exec = malloc(sizeof(t_cmds) * (3));
// 		int	j = 0;
// 		data_exec[0].cmd = ft_strdup("ls -l");
// 		data_exec[1].cmd = ft_strdup("ls -l");
// 		data_exec[2].cmd = ft_strdup("wc -l");
// 		while (j < (3))
// 		{
// 			env_init(&data_exec[j].lst_env, env);
// 			data_exec[j].env = ft_env_cpy(env);
// 			data_exec[j].cmd = ft_strdup(av[j + 1]);
// 			data_exec[j].infile = 0;
// 			data_exec[j].outfile = 1;
// 			data_exec[j].ncmd = 3;
// 			data_exec[j].exit = ex;
// 			j++;
// 		}
// 	}
// 	ret = exec(&data_exec);
// 	if (data_exec)
// 		free(data_exec);
// 	return (0);
// }
 

 // verifier tout les test 
 // cas actuelle ; builtin necrivent pas dans le pipe