/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:50 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/16 17:15:25 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_quote(t_deque *tokens, char *start, char quote)
{
	char	*idx;
	char	*tmp;

	idx = start + 1;
	while (*idx != '\0' && *idx != quote)
		idx++;
	if (*idx == '\0')
	{
		write(2, "Error unmatched quote\n", 23);
		while (tokens->front != NULL)
			delete_front(tokens);
		free(tokens);
		return (0);
	}
	tmp = (char *)malloc(sizeof(char) * (idx - start + 2));
	ft_strlcpy(tmp, start, idx - start + 2);
	insert_rear(tokens, tmp, WORD);
	return (idx + 1);
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
	ft_strlcpy(tmp, start, len + 1);
	insert_rear(tokens, tmp, token_type);
	return (start + len);
}

static char	*process_word(t_deque *tokens, char *start)
// TODO 이전 토큰이 heredoc인지 아닌지 검사하기, heredoc인 경우 그대로
// TODO 이전 토큰이 heredoc아닌데 word 중간에 $나올 경우 환경변수 적용해서 바꿔주기
{
	char	*idx;
	char	*tmp;

	idx = start;
	while (*idx != '\0' && !ft_isspace(*idx)
		&& *idx != '|' && *idx != '>' && *idx != '<' && *idx != '\'' && *idx != '\"')
		idx++;
	tmp = (char *)malloc(sizeof(char) * (idx - start + 1));
	ft_strlcpy(tmp, start, idx - start + 1);
	insert_rear(tokens, tmp, WORD);
	return (idx + 1);
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
		if (*start == '\'')
			start = process_quote(tokens, start, '\'');
		else if (*start == '\"')
			start = process_quote(tokens, start, '\"');
		else if (*start == '|' || *start == '>' || *start == '<')
			start = process_operator(tokens, start, pipecnt);
		else
			start = process_word(tokens, start);
		if (start == 0)
			return (0);
	}
	return (tokens);
}
