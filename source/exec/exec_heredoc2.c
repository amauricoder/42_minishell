/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:13:07 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/24 20:24:23 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

//EXPANSAO
// << EOF -> Expande
// << 'EOF' -> Nao expande (Expansão Desativada)
// << "EOF" -> Nao expande

int	allow_hd_expansion(char *input)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0) // Considera apenas se não estamos dentro de aspas duplas
			s_quotes++;
		else if (input[i] == '\"') // Considera apenas se não estamos dentro de aspas simples
			d_quotes++;
		i++;
	}
	if (d_quotes || s_quotes)
		return (0);
	return(1);
	
}

//Need to refactore this
//problem to be tracked "$USER" ee "$USER";
char	*expand_heredoc(t_mini *mini_d, char *line, int start)
{
	int i;
	int	env_size;
	int	env_start;
	int	env_is_first;
	char	*tmp;
	char	*to_replace;
	char	*line_cpy;
	char	*result;
	char	*env_tmp;
	char	*tmp_end;

	i = ft_strlen_char(line, '$');
	env_is_first = 0;
	if ((int)ft_strlen(line) == 2)
		return (line);
	else if ((i == 0 && line[i] != '$'))
		return (line);	
	if (line[i] && line[i + 1] && line[i + 1] == ' ')
		return (line);
	if (i == 0 && line[i] == '$')
	{
		while(line[i])
		{
			if (line[i] == ' ' || line[i] == '\0' || line[i] == '\n')
				break;
			i ++;
		}
		env_is_first ++;
	}

	line_cpy = ft_strtrim(line, "\n");
	if (env_is_first)
		return (expand_first(mini_d, line_cpy, i));
	else
	{
		printf("Se a variavel expansiva nao eh a primeira palavra \n");
		tmp = ft_substr(line, start, i);
	
		env_size = 0;
		env_start = i;
		while(line[i])
		{
			if (line[i] == ' ' || line[i] == '\0' || line[i] == '\n')
				break;
			env_size ++;
			i ++;
		}

		to_replace = ft_substr(line, env_start, env_size);
		if (env_size == 1)
			env_tmp = ft_strdup("$");
		else
			env_tmp = env_expanded(mini_d, to_replace);
		free(line_cpy);
		free(to_replace);
		while(line[i] != ' ' && line[i] != '\0' && line[i] == '\n')
			i ++;

		tmp_end = ft_substr(line, i, ft_strlen(&line[i]));
		if (ft_strlen(tmp_end) == 0) // isso quer dizer que so existe apenas duas palavras
		{
			printf("So existe duas palavras a serem unidas \n");
			free(tmp_end);
			tmp_end = ft_strjoin(env_tmp, "\n");
			//se existe apenas 2 palavras
			//preciso juntar primeira parte + segunda parte.
			//retornar a juncao delas todas
			line_cpy = ft_strjoin(tmp, tmp_end);
			free(env_tmp);
			free(tmp_end);
			free(tmp);
			return (line_cpy);
		}
		//se chegou aqui, quer dizer que existe 3 partes a serem juntas
		//primeira parte + parte expandida + parte final (que pode ter outros $)
		//tmp - comeco
		//to_replace -- variavel expandida
		//tmp_end -- fina;
		
		//preciso criar uma funcao chamada join_tree, para juntar tres palavras.
		line_cpy = ft_strjoin3(tmp, env_tmp, tmp_end);
		result = expand_heredoc(mini_d, line_cpy, 0);
		free(line_cpy);
		return (result);
	}
	return (NULL);
}

//$ -> $

/**
 * @brief Concatenate 3 strgs in one.
 * Frees the str1, str2 and str3.
 */
char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(str1, str2);
	tmp2 = ft_strjoin(tmp, str3);

	free(tmp);
	free(str1);
	free(str2);
	free(str3);
	return (tmp2);
}