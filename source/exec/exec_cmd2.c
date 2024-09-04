/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 16:28:11 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	treat_exec_exception(void *root)
{
	t_exec	*node;
	int		i;
	int		j;
	int		len;

	node = root;
	i = 0;
	j = 0;
	while (node->args[i])
	{
		len = ft_strlen(node->args[i]);
		if (ft_strlen(node->args[0]) == 0 || node->args[0][len - 1] != '=')
			return (0);
		if (len > 0 && node->args[i][len - 1] == '=')
		{
			if (!node->args[i + 1])
				return (1);
			free(node->args[i]);
			j = i;
			treat_exec_exception_aux(node, &j);
		}
		else
			i++;
	}
	return (0);
}

void	treat_exec_exception_aux(t_exec *exec_nd, int *j)
{
	while (exec_nd->args[*j + 1])
	{
		exec_nd->args[*j] = exec_nd->args[*j + 1];
		(*j)++;
	}
	exec_nd->args[*j] = NULL;
}
