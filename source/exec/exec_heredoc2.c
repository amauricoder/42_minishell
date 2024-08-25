/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:13:07 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/25 16:11:46 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

//EXPANSAO
// << EOF -> Expande
// << 'EOF' -> Nao expande (Expansão Desativada)
// << "EOF" -> Nao expande
int	do_expansion(char *input)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		else if (input[i] == '\"')
			d_quotes++;
		i++;
	}
	if (d_quotes || s_quotes)
		return (0);
	return(1);
	
}

int		handle_heredoc(t_mini *mini_d, t_redir *hd_node)
{
	char	*line;
	int		hd_fd;

	hd_node->hd_tmp = get_heredoc_name(mini_d, mini_d->qt_heredocs ++, 0);
	hd_fd = open(hd_node->hd_tmp, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (hd_fd < 0)
		err_msg(mini_d, NULL, EXIT_FAILURE, 0);
	line = NULL;
	while(1)
	{
		if (write_on_heredoc(mini_d, hd_fd, hd_node, line))
			break;
	}
	get_next_line(-3);
	return (close(hd_fd), EXIT_SUCCESS);
}

char	*hd_expand_heredoc(t_mini *mini_d, char *line)
{
	char	*tmp_final;
	int		i;

	i = 0;
	while (i < (int)ft_strlen(line))
	{
		i += ft_strlen_char(&line[i], '$');
		if (line[i] == '$' && specch(line[i + 1]))
		{
			if (line[i + 1] == '\0')
				break;
			i += 2;
			while (line[i] && !specch(line[i]))
				i++;
			while (line[i] && line[i] != '$')
				i++;
		}
		if (i < (int)ft_strlen(line))
		{
			tmp_final = hd_change_content(mini_d, line, i);
			free(line);
			line = ft_strdup(tmp_final);
			free(tmp_final);
			tmp_final = NULL;
			i = 0;
		}
	}
	return (line);
}

char	*hd_change_content(t_mini *mini_d, char *line, int i)
{
	char	*env_exp;
	char	*tmp;
	char	*tmp_middle;
	char	*tmp_end;

	env_exp = env_expanded(mini_d, &line[i]);
	tmp = ft_substr(line, 0, i);
	tmp_middle = ft_strjoin(tmp, env_exp);
	tmp_end = ft_substr(line,
			i + aftdol_len(&line[i]) + 1,
			ft_strlen(line) - ft_strlen(tmp)
			- aftdol_len(&line[i]) - 1);
	free(tmp);
	if (!ft_strnstr(env_exp, tmp_end, ft_strlen(env_exp)))
		tmp = ft_strjoin(tmp_middle, tmp_end);
	else
		tmp = ft_strdup(tmp_middle);
	free(tmp_middle);
	free(tmp_end);
	free(env_exp);
	return (tmp);
}
