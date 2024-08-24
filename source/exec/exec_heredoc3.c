/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:19:27 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/24 20:17:43 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

char	*expand_first(t_mini *mini_d, char *line, int i)
{
  	char *tmp;
    char *to_replace;
    char *new_line;
	char *result;

    tmp = env_expanded(mini_d, line);
    to_replace = ft_substr(line, i, ft_strlen(&line[i]));
    free(line); // Free the original line
    new_line = ft_strjoin(tmp, to_replace);
    free(to_replace);
    free(tmp);
    result = expand_heredoc(mini_d, new_line, 0);
    free(new_line);
    return (result);
}
