/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:33 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/20 13:21:57 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_add(t_mini *mini, char *str, char *name)
{
	printf("str = %s\n", str);
	printf("name = %s\n", name);
	//procurar se str[0] já existe na export
	//se existir, substituir o valor
		//se o str[0][ft_strlen(str[0]) - 1] == '+', adicionar o valor ao que ja tinha antes
	//if str[1] adiciona na env tbm
	//LEMBRAR DE SEMPRE ADD O = ENTRE AS STRINGS
	//criar um t_env temporario com a string pra adicionar
	//criar um temp do export pra correr até o final
	//temp_exp = env_export(temp_env)
	t_env	*exp_cpy;
	t_env	*env;
	int		i;

	exp_cpy = mini->export;
	env = ft_calloc(sizeof(t_env), 1);
	env->name = ft_strdup(str);
	env->next = NULL;
	i = 0;
	printf("NAME SIZE -> %li\n", ft_strlen(name));
	printf("str[ft_strlen(name) - 1] -> %c\n", str[ft_strlen(name) - 1]);
	while (mini->export)
	{
		printf("compare-> %i\n", ft_strncmp(mini->export->name, str, ft_strlen(name) - 1));
		if (!ft_strncmp(mini->export->name, str, ft_strlen(name)))
		{
			free(mini->export->name);
			mini->export->name = ft_strdup(str);
			return ;
		}
		else if (!ft_strncmp(mini->export->name, str, ft_strlen(name) - 1)
			&& str[ft_strlen(name) - 1] == '+')
		{
			printf("AQUI É PRA SER UM + -> %c\n", str[ft_strlen(name) - 1]);
			while (str[i] != '=')
					i++;
			mini->export->name = ft_strjoin(mini->export->name, &str[++i]);
			return ;
		}
		if (mini->export->next)
			mini->export = mini->export->next;
		else
			break;
	}
	printf("ONDE TA -> %s\n", mini->export->name);
	//chegou no ultimo, tem que adicionar o novo caso nao tenha encontrado
	//criar um novo t_env e adicionar no final
	mini->export->next = ft_calloc(sizeof(t_env), 1);
	mini->export = mini->export->next;
	//aqui nao da certo se nao tiver o =
	mini->export->name = env_export(env);
	mini->export->next = NULL;
	//colocar em ordem
	mini->export = lst_sort(mini->export);
	mini->export = exp_cpy;
	free_env(env);
}

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
			exp = exp->next;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		while (str[++i])
		{
			tmp = ft_split(str[i], '=');//e so pra ver se tem igual ou nao
			printf_matriz(tmp);
			//if (tmp[1])//quer dizer que tinha um "=", lembrar de add ele dps
			//	env_add(mini, str[i]);
			export_add(mini, str[i], tmp[0]);
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
