/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:33 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/18 18:33:47 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_read(t_mini *mini, char **str)
{
	char	**tmp;
	t_env	*exp;

	tmp = str;
	if (!str[1])
	{
		exp = mini->export;
		while (exp)
		{
			printf("%s\n", exp->name);
			exp = exp->next;
		}
		return (EXIT_SUCCESS);
	}
	else if (str[1])
	{
		tmp = ft_split(str[1], '=');
		if (tmp[1])
			env_add(mini, &tmp[0]);
		//export_add(mini, str[1]);
	}
	else
		err_msg(mini, "consertar msg de erro no export pra aceitar so um argumento\n", 1, 0);
	free_matriz(tmp);
	return (EXIT_SUCCESS);
}

int	export_create(t_mini *mini)
{
	int     i;
	t_env   *new;
	t_env   *last;
	t_env	*env_cpy;
	
	i = 0;
	mini->export = NULL; // Garante que a lista começa vazia.
	env_cpy = lst_sort(mini->env_d);
	while (env_cpy)
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->id = i;
		new->name = env_export(env_cpy); // Supondo que env[i] contém o nome da variável de ambiente.
		//mudar a env_export pra fazer malloc da str e pra não receber o segundo parametro
		new->next = NULL;
		if (mini->export == NULL)
			mini->export = new; // Define o primeiro elemento da lista.
		else
			last->next = new; // Adiciona o novo elemento ao final da lista.
		last = new; // Atualiza a referência ao último elemento.
		i++;
		env_cpy = env_cpy->next;
	}
	return (EXIT_SUCCESS);
}

char	*env_export(t_env *env)
{
	char	*str;
	int		i;
	int		j;
	int		size;
	
	i = 0;
	j = 0;
	size = 0;
	while (env->name[size])
			size++;
	size += 13;
	str = ft_calloc(sizeof(char), size + 1);
	ft_strlcpy(str, "declare -x ", 12);
	while (env->name[i] != '=')
		i++;
	ft_strlcpy(&str[11], env->name, i + 2);
	ft_strlcpy(&str[11 + i + 1], "\"", 2);
	while (env->name[i + j])
		j++;
	ft_strlcpy(&str[11 + i + 2], &env->name[i + 1], j);
	ft_strlcpy(&str[11 + i + j + 1], "\"", 2);
	return (str);
}

t_env	*lst_sort(t_env *env)
{
    t_env	*tmp;
    t_env	*tmp2;
    char	*swap;

    if (!env)
        return (NULL);
    tmp = env;
    while (tmp)
    {
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name)) > 0)
            {
                swap = tmp->name;
                tmp->name = tmp2->name;
                tmp2->name = swap;
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
    return (env);
}
