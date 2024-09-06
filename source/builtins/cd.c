/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/06 15:25:25 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_mini *mini, char **str)
{
	char	*dir;
	char	cwd[1024];

	dir = NULL;
	if (str[1] && str[2])
		return (err_msg(mini, ft_strjoin(D_CD, TOO_ARGS), 1, 1));
	if (str[1] && !ft_strncmp(str[1], ".", 1) && !str[1][1])
		return (EXIT_SUCCESS);
	if (!cd_home(mini, str) || !cd_oldpwd(mini, str))
		return (EXIT_SUCCESS);
	else if (str[1])
	{
		if (str[1][0] == '\0')
			return (EXIT_SUCCESS);
		dir = getcwd(cwd, sizeof(cwd));
		if (safe_chdir(mini, str[1]) == -1)
			return (EXIT_FAILURE);
		return (update_pwd_oldpwd(mini, dir));
	}
	return (EXIT_FAILURE);
}

int	cd_home(t_mini *mini, char **str)
{
	char	*dir;
	char	*last_dir;
	char	cwd[1024];

	if ((str[1] && !ft_strncmp(str[1], "--", 2) && !str[1][2]) || !str[1]
		|| (!ft_strncmp(str[1], "~", 1) && !str[1][1]))
	{
		dir = expand(mini, "HOME");
		if (!dir && str[1] && !ft_strncmp(str[1], "~", 1) && !str[1][1])
			dir = getenv("HOME");
		if (!dir)
			return (err_msg(mini, H_NOT, 1, 0));
		last_dir = getcwd(cwd, sizeof(cwd));
		if (safe_chdir(mini, dir) == -1)
			return (EXIT_FAILURE);
		return (update_pwd_oldpwd(mini, last_dir));
	}
	return (EXIT_FAILURE);
}

int	cd_oldpwd(t_mini *mini, char **str)
{
	char	*dir;
	char	*last_dir;
	char	cwd[1024];

	if (str[1] && !ft_strncmp(str[1], "-", 1) && !str[1][1])
	{
		dir = expand(mini, "OLDPWD");
		if (!dir)
			return (err_msg(mini, OLDPWD_NOT, 1, 0));
		last_dir = getcwd(cwd, sizeof(cwd));
		printf("%s\n", dir);
		if (safe_chdir(mini, dir) == -1)
			return (EXIT_FAILURE);
		return (update_pwd_oldpwd(mini, last_dir));
	}
	return (EXIT_FAILURE);
}

int	safe_chdir(t_mini *mini, char *dir)
{
	if (chdir(dir) == -1)
	{
		mini->exit_status = err_msg(mini, join_three(D_CD, dir, NOF, 0), 1, 1);
		return (-1);
	}
	return (EXIT_SUCCESS);
}
