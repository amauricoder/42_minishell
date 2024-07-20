/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/20 13:13:20 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_mini *mini, char **str)
{
	char	cwd[1024];
	char	*dir;	

	if (str[2])
		return (error_msg_and_exit(CD_ERR_ARG, EXIT_FAILURE));
	dir = getcwd(cwd, sizeof(cwd));
	(void)mini;
 	if (!dir)
	{
		perror("minishell: cd: "); //treat this properly with exit_status
		return (EXIT_FAILURE);
	}
	if (!str[1])
		//funcao que encontre o home na mini_d->env
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);	
}