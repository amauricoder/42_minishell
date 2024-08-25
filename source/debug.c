/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:25:38 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/25 17:17:31 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	debug_nodes_and_tree(t_mini *mini_d)
{
	printf(ORANGE"-------- MAIN --------\n"RESET);
	printf("\n");
	printf(MGT"-------- PRINT NODES --------\n"RESET);
	printf("\n");
	print_nodes(mini_d);
	printf("\n");
	printf(MGT"-------- PRINT TREE --------\n"RESET);
	printf("\n");
	print_tree(mini_d->root, "", 0);
	printf("\n");
	printf(ORANGE"-------- END MAIN --------\n"RESET);
}
