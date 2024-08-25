/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:22:27 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/25 16:11:56 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int	write_on_heredoc(t_mini *mini_d, int hd_fd, t_redir *hd_node, char *line)
{
	char	*new_line;
	char	*expanded_line;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	add_history(line);
	if (!line)
		return (1);
	if (!ft_strncmp(line, hd_node->fname, ft_strlen(hd_node->fname))
		&& ft_strlen(line) - 1 == ft_strlen(hd_node->fname))
		return (free(line), 1);
	if (do_expansion(hd_node->fname))
	{
		new_line = ft_strtrim(line, "\n");
		expanded_line = hd_expand_heredoc(mini_d, new_line);
    	if (expanded_line)
		{
    		write(hd_fd, expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
	}
	else
		write(hd_fd, line, ft_strlen(line));
	write(hd_fd, "\n", 1);
	return (free(line), 0);
}
