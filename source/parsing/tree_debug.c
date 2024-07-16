/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:27:11 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/16 17:22:55 by aconceic         ###   ########.fr       */
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
	else if (type == R_IN || type == R_OUT || type == D_R_OUT)
		print_redir(node, prefix, isLeft);
   	/*	else if (type == PIPE)
	{
		t_pipe *pipe = (t_pipe *)node;
		printPipe(pipe, prefix, isLeft);
	} 
	*/
}

//function used for debugging purposes
void	print_exec(void *node, const char *prefix, bool isLeft)
{
	int			i;
	t_exec		*exec;
	const char	*str[] = {"GENERAL", "IN_QUOTE", "IN_DQUOTE", "WORD",
		"W_SPACE", "D_QUOTE", "S_QUOTE", "PIPE", "ENV", "RED_OUT",
		"D_R_OUT", "RED_IN", "HEREDOC", "FILE_NAME"};

	exec = (t_exec *)node;
	printf("%s%s"RED"EXEC: Type = '%s'\n"RESET,
		prefix,
		isLeft ? "├── " : "└── ",
		str[exec->type + 3]);
	i = 0;
	while (exec->args[i])
	{
		printf(MGT"%s    %s\n"RESET, prefix, exec->args[i]);
		i ++;
	}
}

void	print_redir(void *node, const char *prefix, bool isLeft)
{
	t_redir	*redir;
	char	newPrefix[256];

	redir = (t_redir *)node;
	printf("%s%s"ORANGE"REDIR: File Name = '%s'\n"RESET,
		prefix,
		isLeft ? "├── " : "└── ",
		redir->fname);

	snprintf(newPrefix, 
		sizeof(newPrefix),
		"%s%s",
		prefix, isLeft ? "│   " : "    ");

	print_tree(redir->down, newPrefix, false);
}

void print_pipe(t_pipe *pipe, const char *prefix, bool isLeft)
{
	printf("%s%sPIPE:\n", prefix, isLeft ? "├── " : "└── ");
	char newPrefixLeft[256];
	char newPrefixRight[256];
	snprintf(newPrefixLeft, sizeof(newPrefixLeft), "%s│   ", prefix);
	snprintf(newPrefixRight, sizeof(newPrefixRight), "%s    ", prefix);
	print_tree(pipe->left, newPrefixLeft, true);
	print_tree(pipe->right, newPrefixRight, false);
}
