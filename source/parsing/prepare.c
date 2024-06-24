/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:40:18 by ismirand          #+#    #+#             */
/*   Updated: 2024/06/24 15:38:26 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *search_and_replace(char **expanded, char *content);
static char **expand_dolar(t_token *token, char **envp);
static int calc_replace_len(char **expanded, char *content);

int prepare_parsing(t_mini	*mini_d, char **envp)
{
	t_token *	token_head;
	char		**expanded_envs;
	
	token_head = mini_d->token;
	expanded_envs = NULL;
	while (mini_d->token != NULL)
	{
		if(mini_d->token->state != IN_QUOTE
			&& check_dollar(mini_d->token->content) 
				&& can_be_expansive(mini_d->token->content))
		{
			expanded_envs = expand_dolar(mini_d->token, envp);
			search_and_replace(expanded_envs, mini_d->token->content);
			//printf_dpchar(expanded_envs);
			free_dp_char(expanded_envs);
		}
		mini_d->token = mini_d->token->next;
	}
	mini_d->token = token_head;
	(void)envp;
	return (EXIT_SUCCESS);
}


static char **expand_dolar(t_token *token, char **envp)
{
	char **arr;
	int i;
	int j;
	int dollar_pos;
	char *tmp;
	char *tmp_clean;

	arr = ft_split(token->content, ' ');
	tmp_clean = NULL;
	i = 0;
	j = 0;
	dollar_pos = 0;
	//while have arr[i]
	while (arr[i])
	{
		//trim to get off the ' '
		dollar_pos = 0;
		tmp = ft_strtrim(arr[i], "\'");
		free(arr[i]);
		arr[i] = ft_strdup(tmp);
		free(tmp);
		//if the arr[i] is a simple word, I want to ignore it.
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
		else // if the arr[i] have a $
		{
			while(arr[i][dollar_pos] != '$')
				dollar_pos ++;
			tmp = ft_strdup(&arr[i][dollar_pos + 1]);
			if(have_spacial_char(tmp)) //if after getting the word, is there some special char on it, CLEAN
			{
				j = 0;
				while(tmp[j] != have_spacial_char(tmp))
					j ++;
				tmp_clean = ft_substr(tmp, 0, j);
				free(tmp);
				tmp = ft_strdup(tmp_clean);
				free(tmp_clean);
			}
			if (getenv(tmp)) // If there is a ENV with the word
			{
				free(arr[i]);
				arr[i] = ft_strdup(getenv(tmp));
				free(tmp);
			}
			else // If not
			{
				free(arr[i]);
				arr[i] = ft_strdup("");
				free(tmp);
			}
		}
		i ++;
	}
	(void)envp;
	return (arr);
}


static char *search_and_replace(char **expanded, char *content)
{
    int     i;
    int     j;
    int     k;
    int     exp_idx;
    char    *cpy;
    int     len = 0;

    // Calculate the required length for the new string
    len = calc_replace_len(expanded, content);
    cpy = malloc(sizeof(char) * (len + 1));
    if (!cpy)
        return (NULL);

    i = 0;
    k = 0;
    exp_idx = 0;
    while (content[i])
    {
        if (content[i] == '$' && content[i + 1] != '\0')
        {
            // Find variable name
            i++;
            j = 0;
            while (content[i + j] && ft_isalnum(content[i + j]))
                j++;
            
            // Copy the expanded variable
            for (int l = 0; expanded[exp_idx][l]; l++)
            {
                cpy[k++] = expanded[exp_idx][l];
            }
            exp_idx++;
            i += j; // Move to the end of the variable name
        }
        else
            cpy[k++] = content[i++];
    }
    cpy[k] = '\0';
    printf("COPY %s \n", cpy);
    return cpy;
}

static int calc_replace_len(char **expanded, char *content)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (content[++i])
    {
        if (content[i] == '$' && content[i + 1] != '\0')
        {
            i++;
            while (content[i] && ft_isalnum(content[i]))
                i++;
            i--; // Step back to the last alnum character
        }
        else
            len++;
    }
	i = 0;
    while (expanded[i])
    {
        len += ft_strlen(expanded[i]);
		i ++;
    }
	return (len);
}
