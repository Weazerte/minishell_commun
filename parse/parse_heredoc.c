/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:32 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/15 20:19:06 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_heredoc(char *line)
{
	if (!line || ft_strlen(line) <= 2)
		return (NULL);
	while (*line && *(line + 2))
	{
		if (*line == '<' && *(line + 1) == '<')
			return (line + 2);
		line++;
	}
	return (NULL);
}

char	*find_multi_heredoc(char *line, t_env *backup_env)
{
	char	*save;
	char	*tmp;
	int		count;

	save = line;
	tmp = find_heredoc(line);
	count = 0;
	while (tmp)
	{
		tmp = find_heredoc(tmp);
		count++;
	}
	tmp = NULL;
	while (count--)
	{
		tmp = do_heredoc(save, 0, backup_env, line);
		free(save);
		save = tmp;
		if (!save)
			return (NULL);
	}
	return (save);
}

char	*path_file(void)
{
	char	*file_path;

	file_path = build_expanded_line("/tmp/file", "", "");
	return (file_path);
}

void	inside_heredoc(char *limiter, char *file, t_env *backup_env, char *str)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (free(file), perror("open"), exit(1));
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &here_sig);
		line = readline("heredoc>");
		if (!line)
			printf("minishell: warning: end-of-file (wanted `eof')\n");
		if (!line || !ft_strcmp(line, limiter))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free_strs(line, file, limiter);
	free(str);
	ft_free_lst(backup_env);
	close(fd);
	exit(0);
}

char	*do_heredoc(char *line, int i, t_env *backup_env, char *str)
{
	char	*pos;
	char	*delimit;
	char	*file;
	char	*new;

	pos = find_heredoc(line);
	file = path_file();
	if (!file)
		return (NULL);
	signal(SIGQUIT, &is_inside_sig);
	signal(SIGINT, &is_inside_sig);
	if (!pos)
		return (line);
	delimit = find_delimit(pos);
	if (!delimit)
		return (line);
	ft_exec_heredoc(delimit, file, backup_env, str);
	new = delimit_to_path(line, delimit, file);
	free_strs(file, delimit, NULL);
	while (new[++i])
	{
		if (new[i] == '<' && new[i - 1] == '<')
			new[i] = -7;
	}
	return (new);
}
