#include "minishell_parse.h"

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_alpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_redirection(int c)
{
	return (c == '<' || c == '>');
}

int	is_operator(char c)
{
	return (is_redirection(c) || c == '|');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}