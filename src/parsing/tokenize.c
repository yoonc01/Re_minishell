/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:50 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/07 17:43:37 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_quote(t_deque *tokens, char *start, char quote)
{
	char	*idx;
	char	*tmp;

	idx = start;
	while (*idx != '\0' && *idx != quote)
		idx++;
	if (*idx == '\0')
	{
		write(2, "Error unmatched quote\n", 24);
		while (tokens->front != NULL)
			delete_front(tokens);
		free(tokens);
		return (0);
	}
	tmp = (char *)malloc(sizeof(char) * (idx - start + 2));
	insert_rear(tokens, ft_strlcpy(tmp, start, idx - start + 1));
	return (idx + 1);
}

static char	*process_operator(t_deque *tokens, char *start)
{
	char	*tmp;
	size_t	len;

	if (*start == '>' && *(start + 1) == '>')
		len = 2;
	else if (*start == '<' && *(start + 1) == '<')
		len = 2;
	else
		len = 1;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	insert_rear(tokens, ft_strlcpy(tmp, start, len));
	return (start + len);
}

static char	*process_word(t_deque *tokens, char *start)
{
	char	*idx;
	char	*tmp;

	idx = start;
	while (*idx != '\0' && !is_space(*idx)
		&& *idx != '|' && *idx != '>' && *idx != '<')
		idx++;
	tmp = (char *)malloc(sizeof(char) * (idx - start + 1));
	insert_rear(tokens, ft_strlcpy(tmp, start, idx - start));
	return (idx + 1);
}

t_deque	*tokenize(char *input)
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
			start = process_single_quote(tokens, start, '\'');
		else if (*start == '\"')
			start = process_single_quote(tokens, start, '\"');
		else if (*start == '|' || *start == '>' || *start == '<')
			start = process_operator(tokens, start);
		else
			start = process_word(tokens, start);
		if (start == 0)
			return (0);
	}
	return (tokens);
}

int	main()
{
	char *input = "hello I am Hyoyoon >> > < << <| | || 'sdf'";
	t_deque	*tokens = tokenize(input);
	while (tokens != NULL)
	{
		printf("%s\n", tokens->str);
		tokens = tokens->next;
	}
}


}
