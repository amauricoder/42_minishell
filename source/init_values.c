/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:46:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/30 16:46:00 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void get_argv_cp(t_mini *mini_d, char **argv);

/**
 * @brief Initialize the main struct with the values
 * passed from the main function;
*/
void    init_main_struct(t_mini *mini_d, char **argv, char **envp)
{
    //env
    mini_d->env_d = (t_env *)malloc(sizeof(t_env));
    get_env(envp, mini_d->env_d);
    //prompt
    mini_d->prompt = get_prompt_msg(envp);
    get_argv_cp(mini_d, argv);
    //token
    mini_d->token = NULL;
}

/**
 * @brief Get copies of the argv passed from the main function
*/
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