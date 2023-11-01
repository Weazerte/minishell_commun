#include "../inc/minishell.h"

int	find_nbcmd(char *str)
{
	int i;
	int	nbcmd;

	i = 0;
	nbcmd = 1;
	while (str[i])
	{
		if(str[i] == '|')
			nbcmd += 1;
		i++;
	}
	return (nbcmd);
}
int find_next_pipe(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (-1);
}
char **line_to_tab(char *line)
{
	int		nbcmd;
	char	**cmds;
	int		i;
	int		start;
	int		pipe;


	nbcmd = find_nbcmd(line);
	printf("NBCMD = %d\n", nbcmd);
	cmds = malloc((nbcmd + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	i = 0;
	start = 0;
	while ((pipe = find_next_pipe(line + start)) != -1)
	{
		printf("START = %d  - PIPE = %d", start, pipe);
		cmds[i] = ft_strndup(line + start, pipe);
		start += pipe + 1;
		i++;
	}
	cmds[i] = ft_strdup(line + start);
	cmds[i + 1] = NULL;
	return (cmds);
}

t_cmds *tab_to_struct(char **cmds)
{
	int		i;
	int		j;
	t_cmds	*struct_cmds;

	i = 0;
	j = 0;
	while(cmds[i])
		i++;
	struct_cmds = malloc(sizeof(t_cmds)* (i + 1));
	if (!struct_cmds)
		return (NULL);
	while (j < i)
	{
		struct_cmds[j].cmd = ft_strdup(cmds[j]);
		free(cmds[j]);
		j++;
	}
	free(cmds);
	struct_cmds[i].cmd = NULL;
	return (struct_cmds);
}


