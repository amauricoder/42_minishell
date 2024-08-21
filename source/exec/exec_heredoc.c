/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:54:54 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/21 19:19:58 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

int		handle_heredoc(t_mini *mini_d, void *root)
{
	t_redir *hd_node;
	char	*line;
	char	*hd_name;
	int		hd_fd;

	hd_node = root;
	mini_d->qt_heredocs ++;
	hd_node->hd_tmp = get_heredoc_name(mini_d, mini_d->qt_heredocs, 0);
	hd_name = hd_node->hd_tmp;
	hd_fd = open(hd_name, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (hd_fd < 0)
		err_msg(mini_d, NULL, EXIT_FAILURE, 0);
	while(1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (!ft_strncmp(line, hd_node->fname, ft_strlen(hd_node->fname))
			&& ft_strlen(line) - 1 == ft_strlen(hd_node->fname))
			break;
		write(hd_fd, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-3);
	close(hd_fd);
	if (line)
		free(line);
	return (EXIT_SUCCESS);
}

int	redirect_heredoc(t_mini *mini_d, t_redir *node)
{
	int		tmp_fd;

	ft_putstr_fd("nome ->", 2);
	ft_putstr_fd(node->hd_tmp, 2);
	ft_putchar_fd('\n', 2);
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
	void	*tmp;
	t_redir *nd;
	t_pipe	*nd_pipe;

	tmp = root;
	nd = tmp;
	if (nd->type == HEREDOC)
	{
		handle_heredoc(mini, root);
		if (nd->down)
			open_heredocs(mini, nd->down);
		root = tmp;
		return ;
	}
	else if (nd->type == PIPE)
	{
		nd_pipe = (t_pipe *)nd;
		open_heredocs(mini, nd_pipe->left);
		open_heredocs(mini, nd_pipe->right);	
	}
	else if (nd->type == R_IN || nd->type == D_R_OUT
		|| nd->type == R_OUT)
	{
		if (nd->down)
			open_heredocs(mini, nd->down);
	}
}
