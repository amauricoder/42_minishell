/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:55:52 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/17 15:58:06 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_exec(void *root) {
    t_exec *exec = (t_exec *)root;
    free_matriz(exec->args);
    free(exec);
}

void free_redir(void *root) {
    t_redir *redir = (t_redir *)root;
    free_tree(redir->down);  // Free the subtree
	free(redir->fname);
    free(redir);
}

// Recursive function to free the tree
void free_tree(void *root) {
    if (!root)
        return;

    int type = *((int *)root);
    if (type == WORD) {
        free_exec(root);
    } else if (type == R_IN || type == R_OUT || type == D_R_OUT || type == HEREDOC) {
        free_redir(root);
    } else {
        // Here we need to free the PIPE
    }
}