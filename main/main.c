/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:18:18 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/07 16:40:14 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exstatus;

t_cmds *do_parsing(char *start_line)
{
    char *line;
    t_cmds *data_exec;
    int ncmd;
	int	i;

	i = 0;
    line = ft_parsing(start_line);
    if (!line)
        return (NULL);
    line = negative_doublequotes(line);
    ncmd = find_nbcmd(line);
    data_exec = line_to_structs(line);
    if (!data_exec)
    {
        free(line);
        return (NULL);
    }
    while (data_exec[i].cmd)
	{
        data_exec[i].ncmd = ncmd;
        data_exec[i].exit = 0;
		data_exec[i].cmd = ft_positive(data_exec[i].cmd);
		i++;
	}
    free (line);
    return (data_exec);
}
int	main(int ac, char **av, char **env)
{
	char	*start_line;
	t_cmds	*data_exec;
    t_env   *backup_env;
    int exit;

    (void)ac;
    (void)av;
	init_signal();
    env_init(&backup_env, env);
    exit = 0;
    exstatus = 0;
	while (exit == 0)
	{
		start_line = readline("Minishell> ");
		if (!start_line)
			ft_exit();
		data_exec = do_parsing(start_line);
        data_exec->lst_env = backup_env;
        data_exec->env = env_to_tab(data_exec->lst_env);
		// for (int i = 0; data_exec[i].cmds != NULL; i++) {
        // printf("STRUCT[%d] = [%s]\n", i, data_exec[i]);
        // }
        exec(&data_exec);
        backup_env = data_exec->lst_env;
        exit = data_exec->exit;
        if (data_exec)
            free(data_exec);
	}
    ft_free_lst(backup_env);
	return (0);
}
