/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:32:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/27 20:41:11 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Prints the current working directory.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
*/

int    pwd(void)
{
    char   cwd[1024];
    char   *directory;

    directory = getcwd(cwd, sizeof(cwd));
    if (!directory)
    {
        perror("minishell: pwd: ");
        return (EXIT_FAILURE);
    }
    printf("%s\n", directory);
    return (EXIT_SUCCESS);
}