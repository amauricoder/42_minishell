/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:40:18 by ismirand          #+#    #+#             */
/*   Updated: 2024/06/25 20:23:20 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char **expand_dolar(t_token *token);
static char *change_content(t_token *token, int i);

//$"PWD"
//$
//amauri $USER amauri
int prepare_parsing(t_mini	*mini_d, char **envp)
{
	t_token *	token_head;
	char		**expanded_envs;
	
	token_head = mini_d->token;
	expanded_envs = NULL;
	while (mini_d->token != NULL)
	{
		if(mini_d->token->state != IN_QUOTE
			&& check_dollar(mini_d->token->content))
		{
			expand_dolar(mini_d->token);
			free_dp_char(expanded_envs);
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = token_head;
	(void)envp;
	return (EXIT_SUCCESS);
}

/**
 * @brief Get the size of a string after the $ until a special char
 * @return The value of the STR after dollarsing. 
*/
int	aftdol_len(char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	if (content[i] == '$')
		i ++;
	while(content[i] && (!specch(content[i + 1]) && content[i + 1]))
		i ++;
	tmp = ft_substr(content, 1, i);
	free(tmp);
	return (i);
}

char *env_expanded(char *content)
{
	int		i;
	char	*tmp;
	char	*env_expanded;
	
	i = 0;
	env_expanded = ft_strdup("");
	if (content[i] == '$')
		i ++;
	while(content[i] && (!specch(content[i + 1]) && content[i + 1]))
		i ++;
	tmp = ft_substr(content, 1, i);
	if (getenv(tmp))
	{
		free(env_expanded);
		env_expanded = ft_strdup(getenv(tmp));
		free(tmp);
		return (env_expanded);
	}
	free(tmp);
	return (env_expanded);
}
static char **expand_dolar(t_token *token)
{
	int i;
	int len;
	int expand;
	char *tmp_final;

	i = 0;
	len = 0;
	tmp_final = NULL;
	expand = 0;
	while(token->content[i])
	{
		if (token->content[i] == '$' && token->content[i + 1])
		{
			expand ++;
			break;
		}
		i ++;
	}

	if (expand)
	{
		tmp_final = change_content(token, i);
		free(token->content);
		token->content = ft_strdup(tmp_final);
		expand_dolar(token);
	}
	free(tmp_final);
	return (NULL);
}

static char *change_content(t_token *token, int i)
{	
	char *env_exp;
	char *tmp;
	char *tmp_middle;
	char *tmp_end;

	env_exp = env_expanded(&token->content[i]);
	tmp = ft_substr(token->content, 0, i);
	tmp_middle = ft_strjoin(tmp, env_exp);
	tmp_end = ft_substr(token->content, 
		i + aftdol_len(&token->content[i]) + 1, 
			ft_strlen(token->content) - ft_strlen(tmp) 
				- aftdol_len(&token->content[i]) - 1);
	free(tmp);
	tmp = ft_strjoin(tmp_middle, tmp_end);
	free(tmp_middle);
	free(tmp_end);
	free(env_exp);
	return (tmp);
}



