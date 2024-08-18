/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:30:24 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 17:22:11 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	define_builtins(t_mini *mini_d)
{
	t_token	*tmp;

	tmp = mini_d->token;
	while (tmp)
	{
		tmp->builtin = NO_B;
		if (!ft_strncmp(tmp->content, "echo", 4))
			tmp->builtin = ECHO;
		if (!ft_strncmp(tmp->content, "cd", 2))
			tmp->builtin = CD;
		if (!ft_strncmp(tmp->content, "pwd", 3))
			tmp->builtin = PWD;
		if (!ft_strncmp(tmp->content, "export", 6))
			tmp->builtin = EXPORT;
		if (!ft_strncmp(tmp->content, "unset", 5))
			tmp->builtin = UNSET;
		if (!ft_strncmp(tmp->content, "env", 3))
			tmp->builtin = B_ENV;
		if (!ft_strncmp(tmp->content, "exit", 4))
			tmp->builtin = EXIT; 
		tmp = tmp->next;
	}
}

void	tests_builtins(t_mini *mini, void *root)
{
	int		type;
	t_exec	*exec_node;

	type = *((int *)root);
	if (type == WORD)
	{
		exec_node = (t_exec *)root;
		if (exec_node->builtin == ECHO)
			echo(exec_node->args);
		if (exec_node->builtin == PWD)
			pwd(mini, exec_node->args);
		if (exec_node->builtin == CD)
			cd(mini, exec_node->args);
		if (exec_node->builtin == EXIT)
			exit_read(mini, exec_node->args);
		if (exec_node->builtin == EXPORT)
			export_read(mini, exec_node->args);
	}
	//printf("The tipe of the root is %i\n", type);
	//(void)root;

}