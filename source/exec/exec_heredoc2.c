/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:13:07 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 19:53:39 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_expansion(t_redir *node, char *input)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		else if (input[i] == '\"')
			d_quotes++;
		i++;
	}
	if (d_quotes || s_quotes || node->hd_ex)
		return (0);
	return (1);
}

int	handle_heredoc(t_mini *mini_d, t_redir *hd_node)
{
	hd_node->hd_fd = open(hd_node->hd_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	while (g_exit_status != 130)
	{
		if (write_on_heredoc(mini_d, hd_node->hd_fd, hd_node))
			break ;
	}
	get_next_line(-3);
	return (close(hd_node->hd_fd));
}

char	*hd_expand_heredoc(t_mini *mini_d, char *str)
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

/**
 * @param d main struc
 * @param fd hredoc fd
 * @param nd node
 * @param line user input
 */
int	write_on_heredoc(t_mini *d, int fd, t_redir *nd)
{
	char	*new_line;
	char	*expanded_line;
	char	*line;

	line = readline(">");
	if (!line)
		return (1);
	if (!ft_strncmp(line, nd->fname, ft_strlen(nd->fname))
		&& ft_strlen(line) == ft_strlen(nd->fname))
		return (free(line), 1);
	if (do_expansion(nd, nd->fname))
	{
		new_line = ft_strtrim(line, "\n");
		expanded_line = hd_expand_heredoc(d, new_line);
		if (expanded_line)
		{
			write(fd, expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (free(line), 0);
}
