/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:15:14 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/10 16:17:19 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_buildins(t_mini *mini_d)
{
	if (!ft_strncmp(mini_d->token->content, "echo", 4))
		echo(mini_d);
}

//not done. just a scketch
void	echo(t_mini *mini_d)
{
	t_token	*tmp;
	int		fd;
	
	//check if echo is the only command
	//check for flag -n
	//permissoes do open -> CREATE, TRUNCATE
	// > apaga tudo e escreve
	// >> escreve no final (append)
	fd = 1;
	//STDOUT_FILENO = dup(fd);
	tmp = mini_d->token->next;
	while (tmp)
	{
		if (tmp->type == R_OUT)
		{
			//open file, get fd, close
		}
		else if (tmp->type == D_R_OUT)
		{
			
		}
		tmp = tmp->next;
	}
	if (tmp->type == W_SPACE)
		tmp = tmp->next;
	while (tmp && (tmp->type == WORD || tmp->type == W_SPACE))
	{
		ft_putstr_fd(tmp->content, 1);
		tmp = tmp->next;
	}
	(void)fd;
}
