/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:32:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/14 20:14:49 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Prints the current working directory.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
*/

int	buildin_pwd(void)
{
	char	cwd[1024];
	char	*directory;	

	directory = getcwd(cwd, sizeof(cwd));
	if (!directory)
	{
		perror("minishell: pwd: ");
		return (EXIT_FAILURE);
	}
	printf("%s\n", directory);
	return (EXIT_SUCCESS);
}
