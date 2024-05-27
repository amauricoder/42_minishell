/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/27 21:29:09 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env env_var;

	isa_function2();
	am_function();

	get_env(envp, &env_var);
	while(env_var.next != NULL)
	{
		printf("variable name on node %s\n", env_var.env_name);
		env_var = *env_var.next;
	}
	(void)argv;
	(void)argc;
	return (0);
}