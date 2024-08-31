/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:54:54 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/31 13:00:37 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

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
	return(EXIT_SUCCESS);
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

void	open_heredocs(t_mini *mini, void *root)
{
	t_redir *nd;

	if (!root)
		return;
	nd = (t_redir *)root;
	if (nd->type == HEREDOC)
		handle_heredoc(mini, nd);
	else if (nd->type == PIPE)
	{
		open_heredocs(mini, ((t_pipe *)nd)->left);
		open_heredocs(mini, ((t_pipe *)nd)->right);
	}
	if (nd->type == HEREDOC || nd->type == R_IN 
		|| nd->type == D_R_OUT || nd->type == R_OUT)
		open_heredocs(mini, nd->down);
}

