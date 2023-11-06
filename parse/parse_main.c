/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:23 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:40 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nMinishell> ", 12);
}

void	ft_exit(void)
{
	write(1, "\nExit\n", 6);
	exit(0);
}
char	*ft_parsing(char *start_line)
{
	char	*line;

	line = ft_strdup(start_line);
	if (!line)
	{
		ft_exit();
		return (NULL);
	}
	if (*line)
		add_history(line);
	line = check_quotes(line);
	if (!line)
	{
		printf("quote error\n");
		return (NULL);
	}
	if (!syntax_parse(line))
	{
		free(line);
		return (NULL);
	}
	if (has_heredoc(line))
	{
		line = negative_doublequotes(line);
		line = find_multi_heredoc(line);
		line = negative_doublequotes(line);
	}
	if (find_pos_dollar(line) != -1)
		line = expand_all(line);
	//line = ft_positive(line);
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
int	main(void)
{
	struct sigaction	sa;
	char				*line;
	char				*start_line;
	t_cmds				*data_exec;
	int					i;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	while (1)
	{
		start_line = readline("Minishell> ");
		if (!start_line)
			ft_exit();
		line = ft_parsing(start_line);
		if (!line)
			continue ;
		data_exec = line_to_structs(negative_doublequotes(line));
		if (!data_exec)
		{
			free(line);
			free_struct(data_exec);
			break ;
		}
		i = 0;
		while (data_exec[i].cmd)
		{
			data_exec[i].cmd = ft_positive(data_exec[i].cmd);
			printf("FINAL TEST STRUCTURE ..... TAB [%d] = [%s]\n", i,
				data_exec[i].cmd);
			i++;
		}
		free_struct(data_exec);
		free(line);
	}
}
