/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:41:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/15 18:39:40 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//I will need 3 "construct function" , this will alloc 
int build_tree(t_mini *mini_d)
{
	void	*root;
	
	root = parse_exec(mini_d);

	//if tem |
	//parse PIPE
	print_tree(root);
	return (EXIT_SUCCESS);
}


void	*parse_exec(t_mini *mini_d)
{
	t_exec	*exec_node;
	static int id;
	void	*root;

	exec_node = NULL;
	if (have_command(mini_d))
	{
		exec_node = ft_calloc(1, sizeof(t_exec)); //free this
		exec_node->id = id;
		id ++;
		exec_node->args = get_cmd(mini_d);
		exec_node->type = WORD;
		//printf_matriz(exec_node->args);
	}
	else
		exec_node = NULL;
	//parse_redir,
	//if !parse_redir
		//return root
	root = exec_node;
	root = parse_redir(mini_d, root);
	return (root);
}

void	*parse_redir(t_mini *mini_d, void *root)
{
	t_token *last;
	static int id;

	last = get_last_redir(mini_d->token, 1);
	if (last) // // This if will be removed. To prevend seg fault using printf.
	{
		//criar um node de redirect
		//fazer com que ele aponte para o node de exec ou de redirect
		while (last)
		{
			root = create_redir_node(root, id, last);
			id ++;
			last = get_last_redir(last, 0);
			if(!last)
				return (root);
			
		}	
	}
	else // This else will be removed. To prevend seg fault using printf.
	{
		// aqui eh caso nao hava redirects
		printf("No more redirs \n");
	}

	return (root);
}
//type 0 == WORD
int	have_command(t_mini *mini_d)
{
	t_token *current;

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

char	*get_redir_name(t_token *node)
{
	t_token *current;

	current = node;
	while (current && current->type != FILE_NAME)
		current = current->next;
	
	if (current->type != FILE_NAME)
		return (ft_strdup("INVALID"));
	else
		return (ft_strdup(current->content));
}

//Get the last redir token or the last redir token before the pipe
t_token *get_last_redir(t_token *node, int first_interaction)
{
	t_token *last;

	last = node;
	if (first_interaction)
	{
		while (last->next && last->type != PIPE)
			last = last->next;

		while (last)
		{
			if (last->type == R_IN || last->type == R_OUT 
				|| last->type == D_R_OUT)
			return (last);
			last = last->prev;
		}
	}
	else
	{
		if (last->type == R_IN || last->type == R_OUT 
				|| last->type == D_R_OUT)
			last = last->prev;
		while (last)
		{
			if (last->type == R_IN || last->type == R_OUT 
				|| last->type == D_R_OUT)
			return (last);
			last = last->prev;
		}
	}
	return (NULL);
}

t_redir	*create_redir_node(void *down, int id, t_token *node)
{
	t_redir * redir;

	redir = ft_calloc(1, sizeof(t_redir)); // free this after
	redir->id = id;
	id ++;
	redir->fname = get_redir_name(node);
	//printf("parse_redir filename %s\n", redir->fname);
	redir->len = ft_strlen(redir->fname);
	// here I need to update this to update always to exec or another redit pointer
	redir->down = down;
	redir->type = node->type;
	return (redir);
}

//function used for debugging purposes
void print_node(void *node);

void print_tree(void *root)
{
	if (root == NULL)
	{
		printf("Empty tree\n");
		return;
	}
	printf("\n");
	printf("----------- PRINT TREE ----------\n");
	printf("\n");
	print_node(root);
}

void print_node(void *node)
{
	if (!node)
		return;

	int type = *((int *)node);
	if (type == WORD)
	{
		t_exec *exec = (t_exec *)node;
		printf("Exec Node: ID=%d, Type=%d\n", exec->id, exec->type);
		printf_matriz(exec->args);
	
	}
	else if (type == R_IN || type == R_OUT || type == D_R_OUT)
	{
		t_redir *redir = (t_redir *)node;
		printf(BLUE "Redir Node: " RESET "ID=%d, File Name="ORANGE" %s "RESET, redir->id, redir->fname);
		printf(GREEN"Down is pointing to a "RESET);
		print_node(redir->down);
	}
}