/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:15:14 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/19 15:55:21 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	define_builtins(t_mini *mini_d)
{
	t_token	*tmp;

	tmp = mini_d->token;
	while (tmp)
	{
		tmp->builtin = NO_B;
		if (!ft_strncmp(tmp->content, "echo", 4))
			tmp->builtin = ECHO;
		if (!ft_strncmp(tmp->content, "cd", 2))
			tmp->builtin = CD;
		if (!ft_strncmp(tmp->content, "pwd", 3))
			tmp->builtin = PWD;
		if (!ft_strncmp(tmp->content, "export", 6))
			tmp->builtin = EXPORT;
		if (!ft_strncmp(tmp->content, "unset", 5))
			tmp->builtin = UNSET;
		if (!ft_strncmp(tmp->content, "env", 3))
			tmp->builtin = B_ENV;
		if (!ft_strncmp(tmp->content, "exit", 4))
			tmp->builtin = EXIT;
		tmp = tmp->next;
	}
}

//not done. just a scketch
//echo -n oi-> printa oi sem o \n
//echo -nnnnnnn oi-> printa oi sem o \n
//echo -n -n -n oi -> printa oi sem o \n
//echo -noi -> printa -noi
void	echo(char **str)
{
	int	i;
	int	j;
	int	new_line;
	int	print;

	i = 1;
	j = 0;
	new_line = 1;
	print = 0;
	while (str[i])
	{
		print = is_echoflag(str[i], &new_line);
		if (print)
			printf("%s", str[i]);
		i++;
	}
	if (new_line == 1)
		printf("\n");
}

int	is_echoflag(char *str, int *new_line)
{
	int	i;

	i = 0;
	if (str[i++] == '-')
	{
		while (str[i] == 'n')
		{
			if (str[i + 1] == '\0')
			{
				*new_line = 0;
				return (false);
			}
			i++;
		}
	}
	return (true);
}
