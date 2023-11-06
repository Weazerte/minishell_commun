/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:18:18 by eaubry            #+#    #+#             */
/*   Updated: 2023/11/06 19:55:03 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		data_exec[i].cmd = ft_positive(data_exec[i].cmd);
		i++;
	}
    free (line);
    return (data_exec);
}
int	main(char **env)
{
	char	*start_line;
	t_cmds	*data_exec;

	init_signal();
	while (1)
	{
		start_line = readline("Minishell> ");
		if (!start_line)
			ft_exit();
		data_exec = do_parsing(start_line);
		for (int i = 0; data_exec[i].cmds != NULL; i++) {
    printf("STRUCT[%d] = [%s]\n", i, data_exec[i]);
}
	}

	return (0);
}