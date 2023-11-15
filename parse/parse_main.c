/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:23 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/15 20:19:59 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	skip_spaces(const char **line)
{
	while (is_space(**line))
		(*line)++;
}

char	*ft_parsing(char *start_line, t_env *backup_env)
{
	char	*line;

	line = ft_strdup(start_line);
	if (!line)
		return (ft_exit(line, backup_env), NULL);
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
		line = find_multi_heredoc(line, backup_env);
		line = negative_doublequotes(line);
	}
	if (find_pos_dollar(line) != -1)
		line = expand_all(line, backup_env);
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

char	*ft_get_env(t_env *env_list, const char *name)
{
	size_t	var_len;
	char	*env_line;
	char	*sign;
	size_t	key_len;

	var_len = ft_strlen(name);
	while (env_list != NULL)
	{
		env_line = env_list->env_line;
		sign = ft_strchr(env_line, '=');
		if (sign != NULL)
		{
			key_len = sign - env_line;
			if (var_len == key_len && ft_strncmp(env_line, name, var_len) == 0)
			{
				return (sign + 1);
			}
		}
		env_list = env_list->next;
	}
	return (NULL);
}
