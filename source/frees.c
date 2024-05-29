/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/29 20:09:41 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Clean ** of chars.
 * @attention Called at prompt.c;
*/
void	free_prompt_msg(char **dp_char)
{
	int	i;
	i = 0;
	while (dp_char[i])
		free(dp_char[i ++]);
	free(dp_char);
}

//dont forget to free get_argv_cp()