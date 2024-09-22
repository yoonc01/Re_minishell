/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:17:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/22 16:58:29 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <sys/wait.h>


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

typedef struct s_env_node
{
	char				*env_key;
	char				*env_value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct	s_env_list
{
	t_env_node	*head;
	int			size;
}	t_env_list;

typedef struct s_inner_block
{
	char					*str;
	struct s_inner_block	*next;
}	t_inner_block;

typedef struct s_inner_block_list
{
	t_inner_block	*head;
	int				size;
}	t_inner_block_list;

typedef struct s_block
{
	t_inner_block_list	*cmd_list;
	t_inner_block_list	*redirection_list;
}	t_block;

t_deque				*create_deque(void);
void				insert_front(t_deque *dq, char *str, t_token_type token_type);
void				insert_rear(t_deque *dq, char *str, t_token_type token_type);
void				delete_front(t_deque *dq);
void				delete_rear(t_deque *dq);

void				malloc_fail(void);
void				argc_err(void);

int					check_env_add(char *env_key);
int					is_valid_env_key(char c);

int 				check_env_add(char *env_key);
int					is_valid_env_key(char c);

t_env_list			*create_env_list(void);
int 				add_env(char *env, t_env_list *env_list);
void				delete_env_node(char *str, t_env_list *env_list);
void				free_env_list(t_env_list *env_list);

t_deque				*tokenize(char *input, int *pipecnt);

void				process_operator_out(char c, size_t *len, t_token_type *token_type);
void				process_operator_in(char c, size_t *len, t_token_type *token_type);

t_block				*parsing(char *input, int *pipecnt, t_env_list *env_list);

char				*apply_env(char *str, t_env_list *env_list);

char				*remove_single_quote(char *str);
char				*remove_double_quote(char *str);
char				*rm_quote_ap_env(char *cmd, t_env_list *env_list, int is_heredoc);
void				free_parsed_input(t_block *parsed_input, int pipecnt);

char				*my_strndup(char *s, size_t n);
int					my_strcmp(char *s1, char *s2);
char				*ft_strnjoin(char *result, char *str, size_t size);
int					ft_isspace(char c);

t_inner_block_list	*create_inner_block_list(void);
void				add_inner_block(t_inner_block_list *lst, t_inner_block *new_node);
void				free_inner_block(t_inner_block_list *lst);

void				set_signals(void);

void				set_terminal(void);

void				ft_unset(char	*env_key, t_env_list *env_list);
void				ft_env(t_env_list *env_list);
void				ft_export(char *env, t_env_list *env_list);

#endif
