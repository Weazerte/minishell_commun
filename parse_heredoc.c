#include "minishell_parse.h"

char	*find_heredoc(char *line)
{
	if (!line || ft_strlen(line) <= 2)
		return (NULL);
	while (*line && *(line + 2))
	{
		if (*line == '<' && *(line + 1) == '<')
			return(line + 2);
		line ++;
	}
	return (NULL);
}

char *find_multi_heredoc(char *line)
{
	char *save;
	char *tmp;
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
		tmp = save;
		save = do_heredoc(save);
		if(tmp != line && count!= -1)
			free(tmp);
	}
	return (save);
}

char *path_file(void)
{
	char		*count;
	char		*file_path;
	static int	i;

	count = ft_itoa(i++);
	file_path = build_expended_line("/tmp/file", count, "");
	if (count)
		free (count);
	return (file_path);
}

static char *do_heredoc(char *line)
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
	delimit = find_delimiter(pos);
	if (!delimit)
		return (line);
	

}