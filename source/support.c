/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:02:42 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/11 19:38:40 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
Aqui eu tava tentando simplificar o codigo e fazer tudo de uma vez
pra funcionar tem que adicionar um int type na struct principal
e mudar o segundo parametro quando chama a init_token
tava funcionando tudo menos os redirects, e eu nao sei porque
se funcionar pode excluir a get_token_type e todas as funcoes especificas de char,
e ficar com a is_special_char do jeito que ta escrita agora
 */
void	do_lexing_aux(t_mini *mini_d, int i, int state)
{
	int	type;

	type = is_special_char(mini_d->input[i]);
	mini_d->type = type;
	if (type == D_QUOTE || type == S_QUOTE)
	{
		create_token(mini_d, &mini_d->input[i], state, 1);
		state = define_state(mini_d->input[i], state, &i);
	}
	if (type == W_SPACE || type == PIPE	|| type == ENV
		|| type == REDIR_OUT || type == REDIR_IN)
	{
		if (type == REDIR_OUT && is_special_char(mini_d->input[i + 1]) == REDIR_OUT)
		{
			mini_d->type = D_REDIR_OUT;
			create_token(mini_d, &mini_d->input[i++], state, 2);
		}
		if (type == REDIR_IN && is_special_char(mini_d->input[i + 1]) == REDIR_IN)
		{
			mini_d->type = HEREDOC;
			create_token(mini_d, &mini_d->input[i++], state, 2);
		}
		else
			create_token(mini_d, &mini_d->input[i], state, 1);
	}
}

void print_nodes(t_mini *mini_d)
{
    t_token *current;
	const char *str[] = {" GENERAL ", "IN_QUOTE ", "IN_DQUOTE", "WORD   ", "W_SPACE",
		"D_QUOTE", "S_QUOTE", "PIPE   ", "ENV    ", "RED_OUT", "D_R_OUT",
		"RED_IN", "HEREDOC"};

	current = mini_d->token;
	while (current)
	{
		printf("token id %i | ", current->id);
		printf("token state %s | ", str[current->state]);
		printf("token type %s | ", str[current->type + 3]);
		printf("token content %s \n", current->content);
		current = current->next;
	}
}

//treat error here
/**
 * @brief Make the duplication of a word for a specific qt of characters
 * @attention TREAT ERROR DECENTLY
*/
char	*ft_strdup_qt(char *str, int qt)
{
	char	*dup;
	int		i;
	
	dup = malloc(sizeof(char) * qt + 1);
	if (!dup || !qt)
		return (NULL);
	i = 0;
	while(i < qt)
	{
		dup[i] = str[i]; 
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}