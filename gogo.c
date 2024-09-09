/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gogo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:50:50 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/07 18:54:34 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:16:52 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/07 16:04:02 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && (i + 1) < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = 0;
	return (ft_strlen(src));
}

int	ft_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}


typedef struct s_node
{
	char			*str;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_deque
{
	t_node	*front;
	t_node	*rear;
	int		size;
}	t_deque;

t_deque	*create_deque(void)
{
	t_deque	*dq;

	dq = (t_deque *)malloc(sizeof(t_deque));
	dq->front = NULL;
	dq->rear = NULL;
	dq->size = 0;
	return (dq);
}

void	insert_front(t_deque *dq, char *str)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->str = str;
	new->next = dq->front;
	new->prev = NULL;
	if (dq->front == NULL)
		dq->rear = new;
	else
		dq->front->prev = new;
	dq->front = new;
	dq->size++;
}

void	insert_rear(t_deque *dq, char *str)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->str = str;
	new->next = NULL;
	new->prev = dq->rear;
	if (dq->rear == NULL)
		dq->front = new;
	else
		dq->rear->next = new;
	dq->rear = new;
	dq->size++;
}

void	delete_front(t_deque *dq)
{
	t_node	*temp;

	if (dq->front == NULL)
		return ;
	if (dq->front->str != NULL)
		free(dq->front->str);
	temp = dq->front;
	dq->front = dq->front->next;
	if (dq->front == NULL)
		dq->rear = NULL;
	else
		dq->front->prev = NULL;
	free(temp);
	dq->size--;
}

void	delete_rear(t_deque *dq)
{
	t_node	*temp;

	if (dq->rear == NULL)
		return ;
	if (dq->rear->str != NULL)
		free(dq->rear->str);
	temp = dq->rear;
	dq->rear = dq->rear->prev;
	if (dq->rear == NULL)
		dq->front = NULL;
	else
		dq->rear->next = NULL;
	free(temp);
	dq->size--;
}

static char	*process_quote(t_deque *tokens, char *start, char quote)
{
	char	*idx;
	char	*tmp;

	idx = start + 1;
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
	ft_strlcpy(tmp, start, idx - start + 2);
	insert_rear(tokens, tmp);
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
	ft_strlcpy(tmp, start, len + 1);
	insert_rear(tokens, tmp);
	return (start + len);
}

static char	*process_word(t_deque *tokens, char *start)
{
	char	*idx;
	char	*tmp;

	idx = start;
	while (*idx != '\0' && !ft_isspace(*idx)
		&& *idx != '|' && *idx != '>' && *idx != '<')
		idx++;
	tmp = (char *)malloc(sizeof(char) * (idx - start + 1));
	ft_strlcpy(tmp, start, idx - start + 1);
	insert_rear(tokens, tmp);
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
			start = process_quote(tokens, start, '\'');
		else if (*start == '\"')
			start = process_quote(tokens, start, '\"');
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

	char *input = "hello I am Hyoyoon >> > < << <| | || 'sdf' \"sdjk\"  ";
	t_deque	*tokens = tokenize(input);
	while (tokens->front != NULL)
	{
		printf("%s\n", tokens->front->str);
		delete_front(tokens);
	}
}