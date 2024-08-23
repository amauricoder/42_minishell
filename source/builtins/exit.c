/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:29:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/18 17:50:53 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//(!ft_strncmp(mini_d.input, "exit", 4)
//&& ft_strlen(mini_d.input) == 4)
void	exit_read(t_mini *mini, char **str) // exitc
{
	ft_printf("nossa exit\n"); // modifiquei isso
	if (!str[1])
		free_and_exit(mini);
	else if (str[1] && str_digit(str[1]))
		exit_number(mini, str);
	else
	{
		err_msg(mini, EXIT_ERR_NUM, 2, 0);
		free_and_exit(mini);
	}
}

int	exit_number(t_mini *mini, char **str)
{
	int	status;
		
	status = ft_atoi(str[1]);
	if (str[2])
		return (err_msg(mini, EXIT_ERR_ARG, 1, 0));
	else
	{
			while (status < 0)
				status += 256;
			status = status % 256;
			mini->exit_status = status;
			free_and_exit(mini);
	}
	return (EXIT_SUCCESS);
}

//analisa se uma str é numero
//retorna 1 se for numero e 0 se não for
int	str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
