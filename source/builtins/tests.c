/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:30:24 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/19 15:49:17 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Function to test
void	tests_builtins(void *root)
{
	int		type;
	t_exec	*exec_node;

	type = *((int *)root);
	if (type == WORD)
	{
		exec_node = (t_exec *)root;
		if (exec_node->builtin == ECHO)
			echo(exec_node->args);
		
	}
	//printf("The tipe of the root is %i\n", type);
	//(void)root;

}