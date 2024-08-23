/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/23 13:55:39 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	treat_exec_exception(void *root)
{
    t_exec	*exec_nd;
    int		i;
	int		j;
	int		len;

    exec_nd = root;
    i = 0;
	j = 0;
    while (exec_nd->args[i])
    {
        len = ft_strlen(exec_nd->args[i]);
		if (exec_nd->args[0][len - 1] != '=')
			return (0);
        if (len > 0 && exec_nd->args[i][len - 1] == '=')
        {
			if (!exec_nd->args[i + 1])
				return (1);
            free(exec_nd->args[i]);
            j = i;
			treat_exec_exception_aux(exec_nd, &j);
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
