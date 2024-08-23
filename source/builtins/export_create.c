/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:33 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/22 16:33:50 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief joins the export value when used "+="
 * @return the full string joined with the "declare -x" and the double quote
*/
char	*exp_join(char *old, char *to_add, t_env *env)
{
	char	*temp;
	char	*temp2;
	char	*save_name;
	int		i;
	
	i = 0;
	while (old[i] != '=')
		i++;
	save_name = ft_strdup_qt(old, ++i);
	temp = ft_strtrim(ft_strchr(old, '=') + 1, "\"");
	free (old);
	free (env->name);
	temp2 = ft_strjoin(&save_name[11], temp);
	free (save_name);
	free (temp);
	env->name = ft_strjoin(temp2, ft_strchr(to_add, '=') + 1);
	free (temp2);
	return (env->name);
}

//cria a linked list export a partir da linked list env
int	export_create(t_mini *mini)
{
	t_env   *new;
	t_env   *last;
	t_env	*env_cpy;
	
	mini->export = NULL; // Garante que a lista começa vazia.
	env_cpy = mini->env_d;
	while (env_cpy)
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->id = env_cpy->id;
		new->name = env_to_export(env_cpy); // Supondo que env[i] contém o nome da variável de ambiente.
		new->next = NULL;
		if (mini->export == NULL)
			mini->export = new; // Define o primeiro elemento da lista.
		else
			last->next = new; // Adiciona o novo elemento ao final da lista.
		last = new; // Atualiza a referência ao último elemento.
		env_cpy = env_cpy->next;
	}
	mini->export = lst_sort(mini->export);
	return (EXIT_SUCCESS);
}

//transforma cada env em export adicionando declare -x e aspas
char	*env_to_export(t_env *env)
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
	while (env->name[i] && env->name[i] != '=')
		i++;
	ft_strlcpy(&str[11], env->name, i + 2);
	if (env->name[i] != '=')
		return (str);
	ft_strlcpy(&str[11 + i + 1], "\"", 2);
	while (env->name[i + j])
		j++;
	ft_strlcpy(&str[11 + i + 2], &env->name[i + 1], j);
	ft_strlcpy(&str[11 + i + j + 1], "\"", 2);
	return (str);
}

//coloca a linked list export em ordem alfabética
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
			if (ft_strncmp(&tmp->name[11], &tmp2->name[11], ft_strlen(tmp->name)) > 0)
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

int	print_export(t_mini *mini)
{
	t_env	*exp;

	exp = mini->export;
	while (exp)
	{
		printf("%s\n", exp->name);
		exp = exp->next;
	}
	return (EXIT_SUCCESS);
}
