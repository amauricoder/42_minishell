/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:16:49 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/15 22:57:31 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @attention Secondary function for find_expansion()
 * @brief Cleans the excess of white spaces token
 * 0 for WORD, 5 for ENV
*/
void	assemble_word_tokens(t_mini *mini_d)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*to_free;
	char	*c_tmp;

	prev = NULL;
	tmp = mini_d->token;
	while (tmp && tmp->next)
	{
		if ((tmp->type == WORD || tmp->type == ENV)
			&& (tmp->next->type == WORD || tmp->next->type == ENV))
		{
			c_tmp = ft_strdup(tmp->content);
			free(tmp->content);
			tmp->content = ft_strjoin(c_tmp, tmp->next->content);
			tmp->len = ft_strlen(tmp->content);
			tmp->type = tmp->next->type;
			free(c_tmp);
			to_free = tmp->next; //store the next token to free
			tmp->next = tmp->next->next; //skip the next token
			free(to_free->content);
			free(to_free);
			//Do not advance tmp or prev since we need to check the new tmp->next
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	(void)prev;
}

/**
 * @brief Check for how many dollars signs exists in a phrase
 * @return The quantity of dollar signs
*/
int	check_dollar(char *nd_content)
{
	int	i;
	int	qt_dollars;

	if (!nd_content)
		return (0);
	i = 0;
	qt_dollars = 0;
	while (nd_content[i])
	{
		if (nd_content[i] == '$')
			qt_dollars ++;
		i ++;
	}
	return (qt_dollars);
}

/**
 * @brief Check if exists a special char in a word
 * @return If exists, return the sign. If not, return false.
*/
int	have_spacial_char(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (specch(word[i]))
			return (word[i]);
		i ++;
	}
	return (false);
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
	while (content[i] && (!specch(content[i + 1]) && content[i + 1]))
		i ++;
	tmp = ft_substr(content, 1, i);
	free(tmp);
	return (i);
}

/**
 * @brief Get the len of a *str until find a specific char.
*/
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

/* char	*aftdol_position(char *big, char *little)
{
	int	i;
	int	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (little[j] == big[i + j] && big[i + j] != '\0')
			j++;
		if (big && big[i + j + 1] == '$')
			return ((char *)&big[i + j + 1]);
		i++;
	}
	return (NULL);
} */
