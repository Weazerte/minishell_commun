/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:18:18 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/08 23:49:38 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exstatus;

t_cmds *do_parsing(char *start_line, t_env *backup_env)
{
    char *line;
    t_cmds *data_exec;
    int ncmd;
	int	i;

    line = ft_parsing(start_line, backup_env);
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
    i = 0;
    
    while (i < ncmd)
	{
        data_exec[i].infile = 0;
        data_exec[i].outfile = 1;
        data_exec[i].ncmd = ncmd;
        data_exec[i].exit = 0;
		data_exec[i].cmd = ft_positive(data_exec[i].cmd);
		i++;
	}
    free (line);
    return (data_exec);
}

int dothis(t_cmds *data_exec, t_env *lst_env)
{
    int exit;

    exit = 0;
    data_exec->env = env_to_tab(lst_env);
    exec(data_exec, lst_env);
    exit = data_exec->exit;
    if (data_exec)
        free(data_exec);
    return (exit);
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
    while (exit == 0)
	{
		start_line = readline("Minishell> ");
		if (!start_line)
			ft_exit();
        data_exec = do_parsing(start_line, backup_env);
        dothis(data_exec, backup_env);
	}
    ft_free_lst(backup_env);
	return (0);
}
 // REMPLACER LES CMD DANS LES PERROR PAR LA FONCTION REMPLACER LES -7
 // ERREUR PARS AVEC QUOTE PAS FERMER
 //RAJOUTER LES REDIRECTION DE INFILE OUTFILE