/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:46:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/29 20:10:36 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void get_argv_cp(t_mini *mini_d, char **argv);

void    init_main_struct(t_mini *mini_d, char **argv, char **envp)
{
    get_env(envp, mini_d->env_d);
    mini_d->prompt = get_prompt_msg(envp);
    get_argv_cp(mini_d, argv);
}

static void get_argv_cp(t_mini *mini_d, char **argv)
{
    int i;

    i = 0;
    while (argv[i])
        i++;
    mini_d->argv_cp = (char **)malloc(sizeof(char *) * (i + 1));
    //protect malloc
    i = 0;
    while (argv[i])
    {
        mini_d->argv_cp[i] = ft_strdup(argv[i]);
        i++;
    }
    mini_d->argv_cp[i] = NULL;
}