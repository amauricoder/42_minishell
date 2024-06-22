/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:40:18 by ismirand          #+#    #+#             */
/*   Updated: 2024/06/22 14:34:38 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int check_dollar(char *nd_content);
static char **expand_dolar(t_token *token, char **envp);
static int have_spacial_char(char *word);
static void printf_dpchar(char **to_print);
//static char *search_and_replace(char **expanded, char *content);

//static int have_spacial_char(char *word);
//'$USER' -> STATE IN_QUOTE && type WORD ~ [output] = $USER
//"$USER" -> state IN_DQUOTE && type WORD ~ [output] = aconceic

//'$USER>amauri' -> STATE IN_QUOTE && type WORD ~ [output] = $USER>amauri
//"$USER>amauri" -> state IN_DQUOTE && type WORD ~ [output] = aconceic>amauri (file is created)

//"$USER $USING" -> state IN_DQUOTE && type WORD ~ [output] = aconceic
//"USER '$USING'" -> state IN_DQUOTE && type WORD ~ [output] = aconceic ''

//"$USER '$USING' $PWD" ->state IN_DQUOTE && type WORD 
// ~ [output] = aconceic '' /home/aconceic/Documents/42_Git/minishell

//"$USER '$USING>a' $PWD" -> state IN_DQUOTE && type WORD
// ~[output] = aconceic '>a' /home/aconceic/Documents/42_Git/minishell

//$BLA -> state GENERAL && type WORD ~ [output] = NULL

//If the word to be expanded is not in ' ' and is valid, it expands.
//Otherwhise, it will be replaced by a NULL character.
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
			expanded_envs = expand_dolar(mini_d->token, envp);
			//search_and_replace(expanded_envs, mini_d->token->content);
			printf_dpchar(expanded_envs);
			free_dp_char(expanded_envs);
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = token_head;
	(void)envp;
	return (EXIT_SUCCESS);
}

static int check_dollar(char *nd_content)
{
	int	i;
	int	qt_dollars;

	if (!nd_content)
		return (0);
	i = 0;
	qt_dollars = 0;
	while(nd_content[i])
	{
		if (nd_content[i] == '$')
			qt_dollars ++;
		i ++;
	}
	return(qt_dollars);
}

//"abc 'abc$USER' $PWD"
static char **expand_dolar(t_token *token, char **envp)
{
	char **arr;
	int i;
	int j;
	int dollar_pos;
	char *tmp;
	char *tmp_join;

	if (ft_strlen(token->content) == 1)
				return (NULL);
	arr = ft_split(token->content, ' ');
	tmp_join = NULL;
	i = 0;
	j = 0;
	dollar_pos = 0;
	while (arr[i])
	{
		dollar_pos = 0;
		tmp = ft_strtrim(arr[i], "\'");
		free(arr[i]);
		arr[i] = ft_strdup(tmp);
		free(tmp);
		if (!(have_spacial_char(arr[i]) == '$'))
		{
			j = i;
			while(arr[j])
			{
				free(arr[j]);
				arr[j] = ft_strdup(arr[j + 1]);
				j ++;
			}
			i --;
		}
		else
		{
			while(arr[i][dollar_pos] != '$')
				dollar_pos ++;
			tmp = ft_strdup(&arr[i][dollar_pos + 1]);
			if (getenv(tmp))
			{
				//if (dollar_pos == 0)
				//{
					free(arr[i]);
					arr[i] = ft_strdup(getenv(tmp));
					free(tmp);
					free(tmp_join); //added after
				//}
				//else
			//	{
					//tmp_join = ft_strdup_qt(arr[i], dollar_pos);
					//free(arr[i]);
					//arr[i] = ft_strjoin(tmp_join, getenv(tmp));
					//free(tmp_join);
					//free(tmp);
				//}
			}
			else
			{
				//if (dollar_pos == 0)
				//{
					free(arr[i]);
					arr[i] = ft_strdup("");
					free(tmp);
				//}
				/* else
				{
					free(tmp);
					tmp = ft_strdup_qt(arr[i], dollar_pos);
					free(arr[i]);
					arr[i] = ft_strdup_qt(tmp, dollar_pos);
					free(tmp);
				} */
			}
		}
		i ++;
	}

	(void)envp;
	
	return (arr);
}
static int have_spacial_char(char *word)
{
	int i;

	i = 0;
	while (word[i])
	{
		if (specch(word[i]))
			return (word[i]);
		i ++;
	}
	return (false);
}

static void printf_dpchar(char **to_print)
{
	int i;

	i = 0;
	while(to_print[i])
		printf("printed -> %s |\n", to_print[i ++]);	
}
/* static char *search_and_replace(char **expanded, char *content)
{
	int	i;

	i = 0;
	
} */