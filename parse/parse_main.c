/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:23 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 21:58:16 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_parsing(char *start_line)
{
	char	*line;

	line = ft_strdup(start_line);
	if (!line)
		return (ft_exit(), NULL);
	if (*line)
		add_history(line);
	line = check_quotes(line);
	if (!line)
		return (printf("quote error\n"), NULL);
	if (!syntax_parse(line))
		return (free(line), NULL);
	if (has_heredoc(line))
	{
		line = negative_doublequotes(line);
		line = find_multi_heredoc(line);
		line = negative_doublequotes(line);
	}
	if (find_pos_dollar(line) != -1)
		line = expand_all(line);
	return (line);
}
int	free_struct(t_cmds *data_struct)
{
	int	i;

	i = 0;
	if (data_struct == NULL)
		return (0);
	while (data_struct[i].cmd != NULL)
	{
		free(data_struct[i].cmd);
		i++;
	}
	free(data_struct);
	return (0);
}
// int	main(void)
// {
// 	struct sigaction	sa;
// 	char				*line;
// 	char				*start_line;
// 	t_cmds				*data_exec;
// 	int					i;
// 	int					ncmd;

// 	sa.sa_handler = handle_sigint;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);

// 	while (1)
// 	{
// 		start_line = readline("Minishell> ");
// 		if (!start_line)
// 			ft_exit();
// 		line = ft_parsing(start_line);
// 		if (!line)
// 			continue ;
// 		line = negative_doublequotes(line);
// 		ncmd = find_nbcmd(line);
// 		data_exec = line_to_structs(line);
// 		if (!data_exec)
// 		{
// 			free(line);
// 			free_struct(data_exec);
// 			break ;
// 		}
// 		i = 0;
// 		while (data_exec[i].cmd)
// 		{
// 			data_exec[i].cmd = ft_positive(data_exec[i].cmd);
// 			data_exec[i].ncmd = ncmd;
// 			printf("FINAL TEST STRUCTURE ..... TAB [%d] = [%s]\n", i,
// 				data_exec[i].cmd);
// 			i++;
// 		}
// 		free_struct(data_exec);
// 		free(line);
// 	}
// }
