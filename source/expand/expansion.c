/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:40:18 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/25 18:15:05 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Check for expansions on the content of a node
*/
int	find_expansion(t_mini	*mini_d)
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
			expand_dollar(mini_d ,mini_d->token, 0);
			free_matriz(expanded_envs);
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = token_head;
	clean_token(mini_d);
	assemble_word_tokens(mini_d);
	update_word_to_file(mini_d);
	return (EXIT_SUCCESS);
}

/**
 * @attention Secondary function for find_expansion();
 * @brief Search for $ENV, if found, expand and replace in the token content.
*/
void	expand_dollar(t_mini *mini_d, t_token *token, int i)
{
	char	*tmp_final;

	tmp_final = NULL;
	i += ft_strlen_char(&token->content[i], '$');
	if (token->content[i] == '$' && specch(token->content[i + 1]))
	{
		if (token->content[i + 1] == '\0')
			return ;
		i += 2;
		while (token->content[i] && !specch(token->content[i]))
			i ++;
		while (token->content[i] && token->content[i] != '$')
			i ++;
	}
	if (i < (int)ft_strlen(token->content) && token->len > 1)
	{
		tmp_final = change_content(mini_d, token, i);
		free(token->content);
		token->content = ft_strdup(tmp_final);
		token->len = ft_strlen(token->content);
		expand_dollar(mini_d, token, i);
	}
	free(tmp_final);
}

/**
 * @attention Secondary function for expand_dollar;
 * @brief Changes the content of the token with the expansible env var.
 * @return The string with the expanded var.
*/
char	*change_content(t_mini *mini_d, t_token *token, int i)
{
	char	*env_exp;
	char	*tmp;
	char	*tmp_middle;
	char	*tmp_end;

	env_exp = env_expanded(mini_d, &token->content[i]);
	tmp = ft_substr(token->content, 0, i);
	tmp_middle = ft_strjoin(tmp, env_exp);
	tmp_end = ft_substr(token->content,
			i + aftdol_len(&token->content[i]) + 1,
			ft_strlen(token->content) - ft_strlen(tmp)
			- aftdol_len(&token->content[i]) - 1);
	free(tmp);
	if (!ft_strnstr(env_exp, tmp_end, ft_strlen(env_exp)))
		tmp = ft_strjoin(tmp_middle, tmp_end);
	else
		tmp = ft_strdup(tmp_middle);
	free(tmp_middle);
	free(tmp_end);
	free(env_exp);
	return (tmp);
}

/**
 * @attention Secondary function to change_content()
 * @return $USER -> aconceic || ft_strdup("") in case of invalid ENV var
*/
char	*env_expanded(t_mini *mini_d, char *cont)
{
	int		i;
	char	*tmp;
	char	*env_expanded;

	i = 0;
	if (cont && cont[0] && cont[1] && cont[1] == '?')
		return (ft_itoa(mini_d->exit_status));
	if (cont[i] == '$' && ft_isdigit(cont[i + 1]) && cont[i + 1] != '0')
		return (ft_strdup(&cont[i + 2]));
	else if (cont[i] == '$' && ft_isdigit(cont[i + 1]) && cont[i + 1] == '0')
		return (ft_strjoin("./minishell", &cont[i + 2]));
	if (cont[i] == '$')
		i ++;
	if (cont[i] == '\'')
		return (ft_strdup(cont));
	while (cont[i] && (!specch(cont[i + 1]) && cont[i + 1]))
		i ++;
	tmp = ft_substr(cont, 1, i);
	if (ft_getenv(mini_d, tmp))
	{
		env_expanded = ft_strdup(save_env(mini_d, tmp));
		free(tmp);
		return (env_expanded);
	}
	return (free(tmp), ft_strdup(""));
}

/**
 * @attention Secondary function for find_expansion()
 * @brief Cleans the excess of white spaces token
*/
void	clean_token(t_mini *mini_d)
{
	t_token	*tmp;
	t_token	*prev;

	while (mini_d->token && mini_d->token->type == W_SPACE) // changes here because we need the NULL **tmp->len == 0 ||**
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
		if ((tmp->type == W_SPACE && prev->type == W_SPACE)) // changes here because we need the NULL **tmp->len == 0 ||** 
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

//amauri > $po TEST
//This is to update the type from word to file if find a redirect
void	update_word_to_file(t_mini *mini_d)
{
	t_token *head;
	
	head = mini_d->token;
	while(mini_d->token)
	{
		if (mini_d->token->type == R_IN || mini_d->token->type == R_OUT
			|| mini_d->token->type == D_R_OUT || mini_d->token->type == HEREDOC)
		{
			if ((mini_d->token->len == 1 || mini_d->token->len == 2)
				&& (mini_d->token->next))
			{
				while ((mini_d->token->next->next) &&
					(mini_d->token->next->type != WORD
					&& mini_d->token->next->type != ENV))
					mini_d->token = mini_d->token->next;	
				mini_d->token->next->type = FILE_NAME;
			}
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = head;
}
