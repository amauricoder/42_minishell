/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:07:33 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/17 10:52:20 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Check if the arguments are valid
 * @return Boolean. Is valid = true. Not valid = 0.
*/
int	is_argument_valid(int argc, char **env)
{
	if (!argc || argc != 1)
	{	
		ft_putstr_fd(RED"Try \"./minishell\" instead\n"RESET, 2);	
		return (false);
	}
	if (!env)
	{
		ft_putstr_fd(RED"Error\" Undefined ENV\n"RESET, 2);	
		return (false);
	}
	return (true);
}

int	is_input_valid(char *input)
{
	int	i;

	i = 0;
	/* if (input[ft_strlen(input) - 1] == '|')
	{
		
		
	} */
	//return (ft_putendl_fd(RED"Error\n Invalid input"RESET, 2), false);
	while(input[i])
	{
		//printf("input -> %c\n", input[i]);
		i ++;
	}
	return (true);	
}