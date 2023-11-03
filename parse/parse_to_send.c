/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_send.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapierre <mapierre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:14 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/03 22:00:08 by mapierre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_nbcmd(char *str)
{
	int	i;
	int	nbcmd;

	i = 0;
	nbcmd = 1;
	while (str[i])
	{
		if (str[i] == '|')
			nbcmd += 1;
		i++;
	}
	return (nbcmd);
}
int	find_next_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}
/*char *skip_non_printable(char *str, int *j, char *cleaned)
{
    while (*str < 0)
	{
        cleaned[(*j)++] = ft_positive(*str);
        str++;
    }
    return (str);
}*/

/*char *clean_cmd(char *cmd)
{
    int	i;
	int	j;
    char *cleaned;
	
	i = 0;
	j = 0;
	cleaned = malloc(ft_strlen(cmd) + 1);
    if (!cleaned)
        return NULL;
    while (cmd[i] != '\0')
	{
        if (cmd[i] < 0)
            cleaned[j++] = -cmd[i];
		else
		{
            if (cmd[i] != ' ' && cmd[i] != '\t')
                cleaned[j++] = cmd[i];
        	else if (j > 0 && cleaned[j - 1] != ' ')
                cleaned[j++] = ' ';
        }
		i++;
    }
	if (j > 0 && cleaned[j - 1] == ' ')
        j--;
    cleaned[j] = '\0';
    return (cleaned);
}*/

t_cmds	*line_to_structs(char *line)
{
	int		nbcmd;
	int		start;
	int		end;
	int		i;
	t_cmds	*struct_cmds;
	
	nbcmd = find_nbcmd(line);
	start = 0;
	end = 0;
	i = 0;
	struct_cmds = malloc(sizeof(t_cmds) * (nbcmd + 1));
	if (!struct_cmds)
		return (NULL);
	while ((end = find_next_pipe(line + start)) != -1)
	{
		struct_cmds[i].cmd = ft_strndup(line + start, end);
		if (!struct_cmds[i].cmd)
			// gerer l'erreur
			return (NULL);
		start += end + 1;
		i++;
	}
	struct_cmds[i].cmd = ft_strdup(line + start);
	struct_cmds[i + 1].cmd = NULL;
	return (struct_cmds);
}
