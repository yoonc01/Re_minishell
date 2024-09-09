/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:17:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/09 18:35:27 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum e_token_type
{
	WORD = 0,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}	t_token_type;

typedef enum e_grammar_status
{
	ST_START =0,
	ST_REDIRECT,
	ST_WORD
}t_grammar_status;

typedef struct s_block
{
	char			**cmd;
	char			**redirection;
	struct s_block	*next;
}t_block;


typedef struct s_node
{
	char			*str;
	t_token_type	token_type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_deque
{
	t_node	*front;
	t_node	*rear;
	int		size;
}	t_deque;

t_deque	*create_deque(void);
void	insert_front(t_deque *dq, char *str, t_token_type token_type);
void	insert_rear(t_deque *dq, char *str, t_token_type token_type);
void	delete_front(t_deque *dq);
void	delete_rear(t_deque *dq);
void	malloc_fail(void);
void	argc_err(void);
t_deque	*tokenize(char *input, int *pipecnt);

#endif
