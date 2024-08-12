/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:29:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/12 15:50:59 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_shell(t_mini *mini, char **str)
{
	//int	status;

	//status = 0;
	if (str[2])
	{
		error_msg_and_exit(mini, EXIT_ERR_ARG, 2);
		return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}