/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:16:52 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/09 13:57:44 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_deque	*create_deque(void)
{
	t_deque	*dq;

	dq = (t_deque *)malloc(sizeof(t_deque));
	if (dq == NULL)
		malloc_fail();
	dq->front = NULL;
	dq->rear = NULL;
	dq->size = 0;
	return (dq);
}

void	insert_front(t_deque *dq, char *str, t_token_type token_type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		malloc_fail();
	new->str = str;
	new->next = dq->front;
	new->prev = NULL;
	new->token_type = token_type;
	if (dq->front == NULL)
		dq->rear = new;
	else
		dq->front->prev = new;
	dq->front = new;
	dq->size++;
}

void	insert_rear(t_deque *dq, char *str, t_token_type token_type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (new == NULL)
		malloc_fail();
	new->str = str;
	new->next = NULL;
	new->prev = dq->rear;
	new->token_type = token_type;
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
