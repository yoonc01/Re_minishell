/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:50 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 15:15:37 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static char	*process_operator(t_deque *tokens, char *start, int *pipecnt)
{
	char			*tmp;
	size_t			len;
	t_token_type	token_type;

	if (*start == '>')
		process_operator_out(*(start + 1), &len, &token_type);
	else if (*start == '<')
		process_operator_in(*(start + 1), &len, &token_type);
	else
	{
		len = 1;
		token_type = PIPE;
		(*pipecnt)++;
	}
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		malloc_fail();
	ft_strlcpy(tmp, start, len + 1);
	insert_rear(tokens, tmp, token_type);
	return (start + len);
}

static char	*process_word(t_deque *tokens, char *start)
{
	char	*idx;
	char	*tmp;
	int		is_single;
	int		is_double;

	idx = start;
	is_single = 0;
	is_double = 0;
	while (*idx != '\0')
	{
		if (is_double == 0 && *idx == '\'')
			is_single = !is_single;
		else if (is_single == 0 && *idx == '\"')
			is_double = !is_double;
		else if ((is_single == 0 && is_double == 0))
			if (ft_isspace(*idx) || is_operator(*idx))
				break ;
		idx++;
	}
	tmp = (char *)malloc(sizeof(char) * (idx - start + 1));
	if (tmp == NULL)
		malloc_fail();
	ft_strlcpy(tmp, start, idx - start + 1);
	insert_rear(tokens, tmp, WORD);
	return (idx);
}

t_deque	*tokenize(char *input, int *pipecnt)
{
	t_deque	*tokens;
	char	*start;

	tokens = create_deque();
	start = input;
	while (*start != '\0')
	{
		while (*start != '\0' && ft_isspace(*start))
			start++;
		if (*start == '\0')
			break ;
		else if (is_operator(*start))
			start = process_operator(tokens, start, pipecnt);
		else
			start = process_word(tokens, start);
		if (start == 0)
			return (NULL);
	}
	return (tokens);
}
