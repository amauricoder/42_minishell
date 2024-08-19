/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:33 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/19 16:33:38 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//faz a leitura do que deve ser feito com o export
//se nao tiver argumento, só printa a lista export
//se tiver um ou mais argumentos, adiciona na export, um a cada espaço
//se tiver um argumento com =, adiciona na env tbm
int	export_read(t_mini *mini, char **str)
{
	char	**tmp;
	t_env	*exp;
	int		i;

	i = 0;
	tmp = str;
	if (!str[1])
	{
		exp = mini->export;
		while (exp)
		{
			printf("%s\n", exp->name);
			//printf("ID -> %i\n", exp->id);
			//definir os ids dos adicionados como -1 pra conseguir fazer o sort só deles
			exp = exp->next;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		while (str[++i])
		{
			tmp = ft_split(str[i], '=');
			printf_matriz(tmp);
			//if (tmp[1])
			//	env_add(mini, &tmp[0]);
			//export_add(mini, str[1]);
			free_matriz(tmp);
		}
	}
	return (EXIT_SUCCESS);
}

//cria a linked list export a partir da linked list env
int	export_create(t_mini *mini)
{
	int     i;
	t_env   *new;
	t_env   *last;
	t_env	*env_cpy;
	
	i = 0;
	mini->export = NULL; // Garante que a lista começa vazia.
	env_cpy = mini->env_d;
	while (env_cpy)
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->id = i;
		new->name = env_export(env_cpy); // Supondo que env[i] contém o nome da variável de ambiente.
		new->next = NULL;
		if (mini->export == NULL)
			mini->export = new; // Define o primeiro elemento da lista.
		else
			last->next = new; // Adiciona o novo elemento ao final da lista.
		last = new; // Atualiza a referência ao último elemento.
		i++;
		env_cpy = env_cpy->next;
	}
	mini->export = lst_sort(mini->export);
	return (EXIT_SUCCESS);
}

//transforma cada env em export adicionando declare -x e aspas
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
