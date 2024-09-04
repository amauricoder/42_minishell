/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:13:07 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 18:23:23 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_heredoc(t_mini *mini_d, char *str)
{
	char	*tmp_final;
	int		i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		i += ft_strlen_char(&str[i], '$');
		if (str[i] == '$' && specch(str[i + 1]) && (str[i + 1] != '\0'))
		{
			i += 2;
			while ((str[i] && !specch(str[i])) || (str[i] && str[i] != '$'))
				i++;
		}
		if (i < (int)ft_strlen(str))
		{
			tmp_final = hd_change_content(mini_d, str, i);
			free(str);
			str = ft_strdup(tmp_final);
			free(tmp_final);
			tmp_final = NULL;
			i = 0;
		}
	}
	return (str);
}

/**
 * @brief treat heredoc expection EOF"" for expansion
*/
void	heredoc_expand(t_mini *mini)
{
	t_token	*head;
	int flag;

	flag = 0;
	head = mini->token;
	while (mini->token)
	{
		if (mini->token->type == HEREDOC)
		{
			mini->token = mini->token->next;
			while(mini->token->type == W_SPACE)
				mini->token = mini->token->next;
			if (mini->token->state == IN_DQUOTE || mini->token->state == IN_QUOTE)
				flag = 1;
			while(mini->token->type != HEREDOC)
					mini->token = mini->token->prev;
			mini->token->expand_heredoc = flag;
		}
		mini->token = mini->token->next;
	}
	mini->token = head;
}

char	*hd_change_content(t_mini *mini_d, char *line, int i)
{
	char	*env_exp;
	char	*tmp;
	char	*tmp_middle;
	char	*tmp_end;

	env_exp = env_expanded(mini_d, &line[i]);
	tmp = ft_substr(line, 0, i);
	tmp_middle = ft_strjoin(tmp, env_exp);
	tmp_end = ft_substr(line,
			i + aftdol_len(&line[i]) + 1,
			ft_strlen(line) - ft_strlen(tmp)
			- aftdol_len(&line[i]) - 1);
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

int	redirect_heredoc(t_mini *mini_d, t_redir *node)
{
	int		tmp_fd;

	tmp_fd = open(node->hd_tmp, O_RDONLY);
	if (tmp_fd == -1)
		return (err_msg(mini_d, NULL, EXIT_FAILURE, 0));
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
	{
		close(tmp_fd);
		return (err_msg(mini_d, NULL, EXIT_FAILURE, 0));
	}
	close(tmp_fd);
	return (EXIT_SUCCESS);
}

char	*get_heredoc_name(t_mini *mini, int id, int invert)
{
	char	*hd_name;
	char	*hd_itoa;
	int		actual_id;

	if (invert)
	{
		actual_id = mini->qt_heredocs - id + 1;
		hd_itoa = ft_itoa(actual_id);
		hd_name = ft_strjoin("/tmp/hd", hd_itoa);
		free(hd_itoa);
		return (hd_name);
	}
	hd_itoa = ft_itoa(id);
	hd_name = ft_strjoin("/tmp/hd", hd_itoa);
	free(hd_itoa);
	return (hd_name);
}
