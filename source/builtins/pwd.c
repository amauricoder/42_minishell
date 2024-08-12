/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:32:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/12 15:42:37 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Prints the current working directory.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
*/

int	pwd(t_mini *mini, char **str)
{
	char	cwd[1024];
	char	*directory;

	if (str[1] && str[1][0] == '-')
		return (error_msg_and_exit(mini, PWD_ERR, 2));
	directory = getcwd(cwd, sizeof(cwd));
	if (!directory)
	{
		error_msg_and_exit(mini, PWD_ERR_DIR, 2);
		return (EXIT_FAILURE);
	}
	printf("%s\n", directory);
	return (EXIT_SUCCESS);
}
