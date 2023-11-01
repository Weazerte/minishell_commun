#include "minishell_parse.h"

void is_inside_sig(int sig)
{
	if (sig == SIGINT)
		write(1, '\n', 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	j = ft_strlen(s);
	if (len > j - start)
		len = j - start;
	if (!s || (j < start))
		return (ft_strdup(""));
	str = malloc((len + 1) * sizeof (char));
	if (!str)
		return (0);
	j = start;
	i = 0;
	while (s[j] && i < len)
	{
		str[i] = s[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char *find_delimit(char *line)
{
	int	i;

	i = 0;
	while(*line)
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

