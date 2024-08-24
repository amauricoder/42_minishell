/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:49 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/23 15:09:21 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//faz a leitura do que deve ser feito com o export
//se nao tiver argumento, só printa a lista export
//se tiver um ou mais argumentos, adiciona na export, um a cada espaço
//se tiver um argumento com =, adiciona na env tbm
int	export(t_mini *mini, char **str)
{
	char	**tmp;
	t_env	*exp;
	int		i;

	i = 1;
	tmp = str;
	if (str[0][6] == '\0' && !str[1])
		return (print_export(mini));
	while (str[i])
	{
		//ve se o primeiro char é num ou um char especial
		if (!ft_isalpha(str[i][0]))
		{
			err_msg(mini, join_three(EXP, str[i], N_VAL, 0), 1, 1);
			i++;
			continue ;
		}
		tmp = ft_split(str[i], '=');//e so pra ver se tem igual ou nao
		exp = mini->env_d;
		read_arg(str[i], tmp, exp);
		export_add(mini, str[i], tmp[0]);
		free_matriz(tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	read_arg(char *str, char **tp, t_env *exp)//se nao tiver node (dps de apagar todos os env), tem que cria a lista do zero
{
	while ((tp[1] || str[ft_strlen(str) - 1] == '=') && exp)
	{
		if (ft_strlen(tp[0]) - 1 > 0 && tp[0][ft_strlen(tp[0]) - 1] == '+'
			&& !ft_strncmp(exp->name, tp[0], ft_strlen(tp[0]) - 1))
		{
			exp->name = env_join(exp->name, str, exp);
			break ;
		}
		else if (!ft_strncmp(exp->name, tp[0], ft_strlen(tp[0])))
		{
			free(exp->name);
			exp->name = ft_strdup(str);
			break ;
		}
		if (!exp->next)
		{
			exp->next = ft_calloc(sizeof(t_env), 1);
			exp->next->name = ft_strdup(str);
			exp->next->next = NULL;
			break ;
		}
		exp = exp->next;
	}
}

void	export_add(t_mini *mini, char *str, char *name)
{
	t_env	*exp_cpy;
	t_env	*env;
	int		exist;

	exist = 0;
	exp_cpy = mini->export;
	env = ft_calloc(sizeof(t_env), 1);
	env->name = ft_strdup(str);
	env->next = NULL;
	exist = export_add_support(mini, str, name, env);
	if (!exist) //se ainda nao tinha, adiciona no final
	{
		mini->export->next = ft_calloc(sizeof(t_env), 1);
		mini->export = mini->export->next;
		mini->export->name = env_to_export(env);
		mini->export->next = NULL;
		free_env(env);
	}
	mini->export = lst_sort(exp_cpy);
//	mini->export = exp_cpy;
}

int	export_add_support(t_mini *mini, char *str, char *name, t_env *env)
{
	while (mini->export)
	{
		//caso += -> retorna adicionado
		if (!ft_strncmp(&mini->export->name[11], str, ft_strlen(name) - 1)
			&& str[ft_strlen(name) - 1] == '+')
		{
			env->name = exp_join(mini->export->name, str, env);
			mini->export->name = env_to_export(env);
			//mini->export = exp_cpy;
			free_env(env);
			return (1);
		}
		//caso = se ja houver -> substitui
		else if (!ft_strncmp(&mini->export->name[11], str, ft_strlen(name)))
		{
			free(mini->export->name);
			mini->export->name = env_to_export(env);
			//mini->export = exp_cpy;
			free_env(env);
			return (1);
		}
		if (mini->export->next)
			mini->export = mini->export->next;
		else
			break;
	}
	return (0);
}
