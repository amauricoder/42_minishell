/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:32:23 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 14:20:17 by aconceic         ###   ########.fr       */
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
		return (err_msg(mini, PWD_ERR, 2, 0));
	directory = getcwd(cwd, sizeof(cwd));
	if (!directory)
	{
		err_msg(mini, PWD_ERR_DIR, 2, 0);
		return (EXIT_FAILURE);
	}
	printf("%s\n", directory);
	return (EXIT_SUCCESS);
}

int	update_pwd_oldpwd(t_mini *mini, char *last_dir)
{
	char	cwd[1024];
	char	*pwd;
	char	*env;

	pwd = getcwd(cwd, sizeof(cwd));
	env = NULL;
	if (!expand(mini, "PWD"))
		export_add(mini, pwd, "PWD=", 1);
	if (!expand(mini, "OLDPWD"))
		export_add(mini, pwd, "OLDPWD=", 1);
	replace_env_value(mini, "PWD", pwd);
	replace_env_value(mini, "OLDPWD", last_dir);
	free_env(mini->export);
	export_create(mini);
	return (EXIT_SUCCESS);
}
