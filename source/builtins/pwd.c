/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:32:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/20 13:39:49 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Prints the current working directory.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
*/

int	pwd(char **str)
{
	char	cwd[1024];
	char	*directory;

	if (str[1] && str[1][0] == '-')
		return (error_msg_and_exit(PWD_ERR, 2));
	directory = getcwd(cwd, sizeof(cwd));
	if (!directory)
	{
		perror("minishell: pwd: "); //treat this properly with exit_status
		return (EXIT_FAILURE);
	}
	printf("%s\n", directory);
	return (EXIT_SUCCESS);
}
