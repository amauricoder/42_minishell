/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:41:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/13 17:27:34 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//I will need 3 "construct function" , this will alloc 
int build_tree(t_mini *mini_d)
{
	void	*root;
	//enum e_token node_type;

	//node_type = *(enum e_token *) root;
	//if (node_type == WORD)
		//
	//ft_printf("Build_Tree() \n");
	root = parse_exec(mini_d);
	
	t_redir *redir;
	
	redir = (t_redir *)root;
	printf("redir content %s \n", redir->fname);
	//if tem |
	//parse PIPE
	return (EXIT_SUCCESS);
}


void	*parse_exec(t_mini *mini_d)
{
	t_exec	*exec_node;
	static int id;
	void	*root;

	//ft_printf("Parse_exec() \n");
	exec_node = NULL;
	if (have_command(mini_d))
	{
		exec_node = ft_calloc(1, sizeof(t_exec)); //free this
		exec_node->id = id;
		id ++;
		exec_node->args = get_cmd(mini_d);
		//printf_matriz(exec_node->args);
	}

	//parse_redir,
	//if !parse_redir
		//return root
	root = exec_node;
	root = parse_redir(mini_d, exec_node);
	return (root);
}

void	*parse_redir(t_mini *mini_d, t_exec *exec_nd)
{
	t_token *last;
	t_redir *redir;
	static int id;

	redir = NULL;
	last = set_token_tail(mini_d);
	//printf("content of last %s \n", last->content);
	while(last)
	{
		//printf("%s", last->content);
		if (last->type == R_IN || last->type == R_OUT || last->type == D_R_OUT)
		{
			//criar um node de redirect
			//fazer com que ele aponte para o node de exec ou de redirect
			redir = ft_calloc(1 ,sizeof(t_redir *)); // free this after
			redir->id = id;
			id ++;
			if (last->len > 2)
				redir->fname = ft_strdup(last->content);
			else if (last->len <= 2 && last->next->next)
				redir->fname = ft_strdup(last->next->next->content);
			redir->down = exec_nd;
			return (redir);
		}
		last = last->prev;
	}
	return (NULL);
}
//type 0 == WORD
int	have_command(t_mini *mini_d)
{
	t_token *current;

	ft_printf("Have_command()\n");
	current = mini_d->token;
	while(current)
	{
		if (current->type == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

//TYPE 4 == PIPE;
char	**get_cmd(t_mini *mini_d)
{
	t_token *current;
	t_token *head;
	char **args;
	int		i;

	//printf("Get_cmd()\n");
	current = mini_d->token;
	head = mini_d->token;
	i = 0;
	args = NULL;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD)
			i ++;
		current = current->next;
	}
	if (i == 0)
		return (NULL);
	current = head;
	args = ft_calloc(i + 1, sizeof(char *)); //free this
	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD)
		{
			args[i] = ft_strdup(current->content);
			i ++;
		}
		current = current->next;
	}
	return (args);
}
