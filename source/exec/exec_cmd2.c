/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 16:46:16 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* int	treat_exec_exception(t_exec *exec_node)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (exec_node->args[i])
	{
		len = ft_strlen(exec_node->args[i]);
		if (ft_strlen(exec_node->args[0]) == 0 || exec_node->args[0][len - 1] != '=')
			return (0);
		if (len > 0 && exec_node->args[i][len - 1] == '=')
		{
			if (!exec_node->args[i + 1])
				return (1);
			free(exec_node->args[i]);
			j = i;
			treat_exec_exception_aux(exec_node, &j);
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
} */

#include <string.h> // para utilizar strchr

int	treat_exec_exception(t_exec *exec_node)
{
	int		i;
	int		j;
	int		len;
	char	*equal_pos;

	i = 0;
	j = 0;
	while (exec_node->args[i])
	{
		len = ft_strlen(exec_node->args[i]);

		// Encontrar a posição de '=' na string
		equal_pos = strchr(exec_node->args[i], '=');

		// Se encontrarmos um '=' na string (não importa onde), ignoramos esse argumento
		if (equal_pos)
		{
			// Verificar se há um próximo argumento, se não houver, retornamos 1 (erro)
			if (!exec_node->args[i + 1])
				return (1);

			// Liberar a memória do argumento atual
			free(exec_node->args[i]);

			// Remover o argumento e ajustar os índices com a função auxiliar
			j = i;
			treat_exec_exception_aux(exec_node, &j);
		}
		else
		{
			// Se não houver '=', passamos para o próximo argumento
			i++;
		}
	}
	return (0);
}

void	treat_exec_exception_aux(t_exec *exec_nd, int *j)
{
	while (exec_nd->args[*j + 1])
	{
		// Mover os argumentos à esquerda
		exec_nd->args[*j] = exec_nd->args[*j + 1];
		(*j)++;
	}
	// Definir o último argumento como NULL
	exec_nd->args[*j] = NULL;
}


