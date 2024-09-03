/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:22:27 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 19:55:08 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief treat heredoc expection EOF"" for expansion
*/
void	heredoc_expand_exception(t_mini *mini)
{
	t_token	*head;

	head = mini->token;
	while (mini->token)
	{
		if (mini->token->type == HEREDOC)
		{
			while (mini->token->type != WORD)
				mini->token = mini->token->next;
			if (mini->token->next && mini->token->next->len == 0)
			{
				while (mini->token->type != HEREDOC)
					mini->token = mini->token->prev;
				mini->token->hd_exception ++;
			}
		}
		mini->token = mini->token->next;
	}
	mini->token = head;
}
