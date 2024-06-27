/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:40:18 by ismirand          #+#    #+#             */
/*   Updated: 2024/06/27 14:37:42 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//$"PWD"
//$
//amauri $USER amauri
//"$'USER' palavra"
void	clean_token(t_mini *mini_d)
{
	t_token	*tmp;
	t_token	*prev;

	while (mini_d->token && (mini_d->token->len == 0
			|| mini_d->token->type == W_SPACE))
	{
		tmp = mini_d->token->next;
		free(mini_d->token->content);
		free(mini_d->token);
		mini_d->token = tmp;
	}
	prev = mini_d->token;
	tmp = mini_d->token;
	while (tmp)
	{
		if (tmp->len == 0 || (tmp->type == W_SPACE && prev->type == W_SPACE))
		{
			prev->next = tmp->next;
			free(tmp->content);
			free(tmp);
			tmp = prev;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/**
 * @brief Check for expansions on the content of a node
*/
//mini_d->token->state != IN_QUOTE
int	check_expansion(t_mini	*mini_d)
{
	t_token	*token_head;
	char	**expanded_envs;

	token_head = mini_d->token;
	expanded_envs = NULL;
	while (mini_d->token != NULL)
	{
		if (mini_d->token->state != 1
			&& check_dollar(mini_d->token->content))
		{
			expand_dollar(mini_d->token);
			free_dp_char(expanded_envs);
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = token_head;
	clean_token(mini_d);
	return (EXIT_SUCCESS);
}

/**
 * @return $USER -> aconceic || ft_strdup("") in case of invalid ENV var
*/
char	*env_expanded(char *content)
{
	int		i;
	char	*tmp;
	char	*env_expanded;

	i = 0;
	if (content[1] == '?')
		return (ft_itoa(g_exit_status));
	env_expanded = ft_strdup("");
	if (content[i] == '$')
		i ++;
	while (content[i] && (!specch(content[i + 1]) && content[i + 1]))
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

int	ft_strlen_char(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			break ;
		i ++;
	}
	return (i);
}

/**
 * @brief Search for $ENV, if found, expand and replace in the token content.
*/
void	expand_dollar(t_token *token)
{
	int		i;
	char	*tmp_final;

	tmp_final = NULL;
	i = ft_strlen_char(token->content, '$');
	if (i < (int)ft_strlen(token->content) && token->len > 1)
	{
		tmp_final = change_content(token, i);
		free(token->content);
		token->content = ft_strdup(tmp_final);
		token->len = ft_strlen(token->content);
		expand_dollar(token);
	}
	free(tmp_final);
}

/**
 * @brief Changes the content of the token with the expansible env var.
 * @return The string with the expanded var.
*/
char	*change_content(t_token *token, int i)
{
	char	*env_exp;
	char	*tmp;
	char	*tmp_middle;
	char	*tmp_end;

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
