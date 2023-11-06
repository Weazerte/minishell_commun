/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:39 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:40 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_delimit(char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (*line == '\0')
			return (NULL);
		if (is_operator(*line))
			return (NULL);
		while (*(line + i) != '\0' && !is_space(*(line + i)))
			i++;
		if (!ft_strncmp(line, "/tmp/file", 9))
			return (find_delimit(has_heredoc(line)));
		return (ft_substr(line, 0, i));
	}
	return (NULL);
}

char	*has_heredoc(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (NULL);
	while (*line && *(line + 2))
	{
		if (*line == '<' && *(line + 1) == '<')
			return (line + 2);
		line++;
	}
	return (NULL);
}

void	ft_exec_heredoc(char *limiter, char *file)
{
	int	pid;
	int	status;
	int	exit_st;

	pid = fork();
	if (pid == 0)
		inside_heredoc(limiter, file);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
		}
		else if (WIFEXITED(status))
		{
			exit_st = WEXITSTATUS(status);
			if (exit_st != 0)
			{
			}
		}
	}
}

char	*delimit_to_path(char *line, char *limiter, char *filename)
{
	char	*new;
	char	*before;
	char	*after;
	char	*point;
	int		pos;

	point = has_heredoc(line);
	pos = ft_strnstr(point, limiter, ft_strlen(point)) - line;
	before = ft_substr(line, 0, pos);
	if (!ft_strncmp(line, "/tmp/file", 9))
		free(line);
	after = ft_strnstr(point, limiter, ft_strlen(point)) + ft_strlen(limiter);
	new = build_expanded_line(before, filename, after);
	free_strs(before, NULL, NULL);
	return (new);
}
