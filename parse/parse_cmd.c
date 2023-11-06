/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:14 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/06 18:47:40 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmds	*free_struct_error(t_cmds *struct_cmds, int pos)
{
	while (pos > 0)
		free(struct_cmds[pos--].cmd);
	return (NULL);
}

t_cmds	*init_struct_cmds(int nbcmd)
{
	t_cmds	*struct_cmds;

	struct_cmds = (t_cmds *)malloc(sizeof(t_cmds) * (nbcmd + 1));
	if (struct_cmds)
		struct_cmds[nbcmd].cmd = NULL;
	return (struct_cmds);
}

char	*create_and_clean_split(char *line, int start, int len)
{
	char	*split;
	char	*cleaned_split;

	split = ft_strndup(line + start, len);
	if (!split)
		return (NULL);
	cleaned_split = rmv_spaces_quotes(split);
	free(split);
	return (cleaned_split);
}

t_cmds	*process_splits(char *line, t_cmds *struct_cmds, int *start, int *i)
{
	int		end;
	char	*cleaned_split;

	end = find_next_pipe(line + *start);
	while (end != -1)
	{
		cleaned_split = create_and_clean_split(line, *start, end);
		if (!cleaned_split)
			return (free_struct_error(struct_cmds, *i));
		struct_cmds[*i].cmd = cleaned_split;
		*start += end + 1;
		(*i)++;
		end = find_next_pipe(line + *start);
	}
	cleaned_split = create_and_clean_split(line, *start,
			ft_strlen(line + *start));
	if (!cleaned_split)
		return (free_struct_error(struct_cmds, *i));
	struct_cmds[*i].cmd = cleaned_split;
	return (struct_cmds);
}

t_cmds	*line_to_structs(char *line)
{
	int		nbcmd;
	int		start;
	int		i;
	t_cmds	*struct_cmds;

	nbcmd = find_nbcmd(line);
	if (nbcmd < 0)
		return (NULL);
	start = 0;
	i = 0;
	struct_cmds = init_struct_cmds(nbcmd);
	if (!struct_cmds)
		return (NULL);
	if (!process_splits(line, struct_cmds, &start, &i))
		return (NULL);
	return (struct_cmds);
}
