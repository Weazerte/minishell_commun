/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:28:17 by mapierre          #+#    #+#             */
/*   Updated: 2023/11/09 17:13:24 by eaubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*dollar_qm(void)
{
	char	*var;

	var = malloc(2);
	if (!var)
		return (NULL);
	var[0] = '0' + g_exstatus;
	var[1] = '\0';
	return (var);
}

char	*negative_doublequotes(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				line[i++] *= -1;
		}
		i++;
	}
	return (line);
}


void csq(char *dest, const char *src, int *j, int *i)
{
    char current_char;

	current_char = src[*i];
    if (*j > 0 && !is_space(dest[*j - 1])) {
        dest[(*j)++] = -7;
    }
    dest[(*j)++] = current_char;
    if (current_char == '>' && src[*i + 1] == '>') {
        dest[(*j)++] = src[++(*i)];
    }
    if (src[*i + 1] != '\0' && !is_space(src[*i + 1])) {
        dest[(*j)++] = -7;
    }
}

char *clean_spaces_quotes(char *dest, const char *src, int *j, int i)
{
    char current_char;

    current_char = src[i];
    while (current_char != '\0')
	{
        if (current_char == '<' || current_char == '>')
            csq(dest, src, j, &i);
        else if (!is_space(current_char))
		{
            if (current_char == '|' && *j > 0 && is_space(dest[*j - 1]))
                (*j)--;
            dest[(*j)++] = current_char;
        }
        else if (!is_space(src[i + 1]) && src[i + 1] != '\0' && src[i + 1] != '|' && src[i + 1] != '<' && src[i + 1] != '>')
            dest[(*j)++] = -7;
        current_char = src[++i];
    }
    dest[*j] = '\0';
    printf("DEST = [%s]", dest);
    return dest;
}

char	*rmv_spaces_quotes(char *line)
{
	char	*new_line;
	int		j;

	j = 0;
	new_line = (char *)malloc(strlen(line) + 1);
	if (!new_line)
		return (NULL);
	skip_spaces((const char **)&line);
	new_line = clean_spaces_quotes(new_line, line, &j, 0);
	while (j > 0 && is_space(new_line[j - 1]))
		j--;
	new_line[j] = '\0';
	return (new_line);
}
