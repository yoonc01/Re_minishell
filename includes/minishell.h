/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:17:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/18 15:55:29 by hyoyoon          ###   ########.fr       */
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
	ST_START = 0,
	ST_REDIRECT,
	ST_WORD
}	t_grammar_status;

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

typedef struct s_env_list
{
	char				*env_key;
	char				*env_value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_inner_block
{
	char					*str;
	struct s_inner_block	*next;
}	t_inner_block;

typedef struct s_block
{
	t_inner_block	**cmd_list;
	t_inner_block	**redirection_list;
}t_block;

t_deque	*create_deque(void);
void	insert_front(t_deque *dq, char *str, t_token_type token_type);
void	insert_rear(t_deque *dq, char *str, t_token_type token_type);
void	delete_front(t_deque *dq);
void	delete_rear(t_deque *dq);
void	malloc_fail(void);
void	argc_err(void);
t_deque	*tokenize(char *input, int *pipecnt);

void	process_operator_out(char c, size_t *len, t_token_type *token_type);
void	process_operator_in(char c, size_t *len, t_token_type *token_type);

int 	add_new_list(char *env, t_env_list **env_list);
void	free_env_list(t_env_list **env_list);
t_block	*parsing(char *input, int *pipecnt, t_env_list **env_list);

char	*apply_env(char *str, t_env_list **env_list);

char	*remove_single_quote(char *str);
char	*remove_double_quote(char *str);
char	*rm_quote_ap_env(char *cmd, t_env_list **env_list, int is_heredoc);
void	free_parsed_input(t_block *parsed_input, t_deque *tokens, int block_i);
void	free_inner_block(t_inner_block **lst);

int		is_valid_env_key(char c);

char	*my_strndup(char *s, size_t n);
int		my_strcmp(char *s1, char *s2);
char	*ft_strnjoin(char *result, char *str, size_t size);
int		ft_isspace(char c);

#endif
