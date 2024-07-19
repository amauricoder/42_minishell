/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:27:11 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/19 13:37:10 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tree(void *node, const char *prefix, bool isLeft)
{
	int	type;

	if (!node)
		return ;
	type = *((int *)node);
	if (type == WORD)
		print_exec(node, prefix, isLeft);
	else if (type == R_IN || type == R_OUT
		|| type == D_R_OUT || type == HEREDOC)
		print_redir(node, prefix, isLeft);
	else if (type == PIPE)
		print_pipe(node, prefix, isLeft);
}

//function used for debugging purposes
void	print_exec(void *node, const char *prefix, bool isLeft)
{
	int			i;
	t_exec		*exec;
	const char	*str[] = {"GENERAL", "IN_QUOTE", "IN_DQUOTE", "WORD",
		"W_SPACE", "D_QUOTE", "S_QUOTE", "PIPE", "ENV", "RED_OUT",
		"D_R_OUT", "RED_IN", "HEREDOC", "FILE_NAME"};
	const char	*built[] = {"NO_B", "ECHO", "CD", "PWD", "EXPORT",
		"UNSET", "ENV", "EXIT"};
	char		*arrow;

	if (isLeft)
		arrow = ft_strdup("├── ");
	else
		arrow = ft_strdup("└── ");
	exec = (t_exec *)node;
	printf("%s%s"RED"EXEC: Type = '%s' - %s\n"RESET,
		prefix,
		arrow,
		str[exec->type + 3],
		built[exec->builtin]);
	free(arrow);
	i = 0;
	while (exec->args[i])
	{
		printf(MGT"%s    %s\n"RESET, prefix, exec->args[i]);
		i ++;
	}
}

void	print_redir(void *node, const char *prefix, bool isLeft)
{
	t_redir		*redir;
	char		new_prefix[256];
	const char	*str[] = {"GENERAL", "IN_QUOTE", "IN_DQUOTE", "WORD",
		"W_SPACE", "D_QUOTE", "S_QUOTE", "PIPE", "ENV", "RED_OUT",
		"D_R_OUT", "RED_IN", "HEREDOC", "FILE_NAME"};
	char		*arrow;

	if (isLeft)
		arrow = ft_strdup("├── ");
	else
		arrow = ft_strdup("└── ");
	redir = (t_redir *)node;
	printf("%s%s"ORANGE"%s: File Name = '%s'\n"RESET,
		prefix,
		arrow,
		str[redir->type + 3],
		redir->fname);
	free(arrow);
	if (isLeft)
		snprintf(new_prefix, sizeof(new_prefix),
			"%s%s", prefix, "│   ");
	else
		snprintf(new_prefix, sizeof(new_prefix),
			"%s%s", prefix, "    ");
	print_tree(redir->down, new_prefix, false);
}

void	print_pipe(void *node, const char *prefix, bool isLeft)
{
	t_pipe	*pipe;
	char	new_prefix_left[256];
	char	new_prefix_right[256];
	char	*arrow;

	pipe = (t_pipe *)node;
	if (isLeft)
		arrow = ft_strdup("├── ");
	else
		arrow = ft_strdup("└── ");
	printf("%s%sPIPE:\n", prefix, arrow);
	free(arrow);
	snprintf(new_prefix_left, sizeof(new_prefix_left), "%s│   ", prefix);
	snprintf(new_prefix_right, sizeof(new_prefix_right), "%s    ", prefix);
	print_tree(pipe->left, new_prefix_left, true);
	print_tree(pipe->right, new_prefix_right, false);
}
