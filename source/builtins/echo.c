/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:15:14 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/20 13:34:17 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//not done. just a scketch
//echo -n oi-> printa oi sem o \n
//echo -nnnnnnn oi-> printa oi sem o \n
//echo -n -n -n oi -> printa oi sem o \n
//echo -noi -> printa -noi
void	echo(char **str)
{
	int	i;
	int	new_line;
	int	print;

	i = 1;
	new_line = 1;
	print = 0;
	while (str[i])
	{
		print = is_echoflag(str[i], &new_line);
		if (print)
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
		}
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
