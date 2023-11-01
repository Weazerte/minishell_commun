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

int	main(int ac, char **av)
{
	struct sigaction	sa;
	char				*line;
	//char				*hdoc;
	char				**cmds;
	t_cmds				*data_exec;
	int					i;
	(void)ac;
	(void)av;
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	// printf("%s\n", env[0]);
	// printf("%s\n", env[1]);
	// printf("%s\n", env[2]);
	// printf("%s\n", env[3]);
	//hdoc = NULL;
	cmds = NULL;

	while (1)
	{
		// printf(MAGENTA "Minishell> " RESET);
		line = readline("Minishell> ");
		if (!line)
		{
			ft_exit();
			continue ;
		}
		if (line && *line)
			add_history(line);
		if (line)
		{
			line = check_quotes(line);
			if (!line)
			{
				printf("quote error\n");
				continue ;
			}
			printf("AFTER QUOTES = %s \n", line);
			if (!syntax_parse(line))
			{
				free(line);
				continue ;
			}
			if (find_pos_dollar(line) != (size_t)-1)
				line = split_env(line);
			// if(find_heredoc(line))
			//{
			//	hdoc = find_multi_heredoc(line);
			//}
			line = ft_positive(line);
			cmds = line_to_tab(line);
			//ENVOYER A LA PLACE DE LINE  LA LIGNE aVEc -1 au lieu des pipes;
			data_exec = tab_to_struct(cmds);
			if (!data_exec)
			{
				free(line);
				//GERER LERREUR
				return (0);
			}
			i = 0;
			while (data_exec[i].cmd)
			{
				printf("TAB %d ======= %s\n", i, data_exec[i].cmd);
				i++;
			}
		}
		free(line);
	}
}

