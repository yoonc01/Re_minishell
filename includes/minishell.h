/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:17:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/05 11:32:20 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct s_buf
{
	char	read_buf[BUFFER_SIZE + 1];
	int		idx;
	int		used;
}t_buf;

typedef enum e_token_type
{
	WORD = 0,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}	t_token_type;

typedef enum e_cmd_type
{
	B_NULL = 0,
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT,
	NONBUILTIN
}	t_cmd_type;

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

typedef struct s_env_list
{
	t_env_node	*head;
	int			size;
}	t_env_list;

typedef struct s_inner_block
{
	char					*str;
	int						type;
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

typedef struct s_child_util
{
	int	pipe_i;
	int	pipecnt;
	int	prev_pipe;
	int	pipefd[2];
	int	childfd[2];
	int	last_child_pid;
	int	last_child_status;
}	t_child_util;

typedef struct s_blackhole
{
	t_env_list	*env_list;
	t_block		*parsed_input;
	int			pipe_cnt;
	int			exit_code;
}	t_blackhole;

t_deque				*create_deque(void);
void				insert_front(t_deque *dq, char *str,
						t_token_type token_type);
void				insert_rear(t_deque *dq, char *str,
						t_token_type token_type);
void				delete_front(t_deque *dq);
void				delete_rear(t_deque *dq);

void				malloc_fail(void);
void				argc_err(void);

int					check_env_add(char *env_key);
int					is_valid_env_key(char c);

int					check_env_add(char *env_key);
int					is_valid_env_key(char c);

t_env_list			*create_env_list(void);
int					add_env(char *env, t_env_list *env_list);
void				delete_env_node(char *str, t_env_list *env_list);
void				free_env_list(t_env_list *env_list);

t_deque				*tokenize(char *input, int *pipecnt);

void				process_operator_out(char c, size_t *len,
						t_token_type *token_type);
void				process_operator_in(char c, size_t *len,
						t_token_type *token_type);

void				parsing(char *input, t_blackhole *blackhole);

char				*apply_env(char *token_word, t_blackhole *blackhole);

char				*process(char *cmd, t_blackhole *blackhole, int is_heredoc);
void				free_parsed_input(t_block *parsed_input, int pipecnt);
void				free_invalid(t_block *parsed_input,
						t_deque *tokens, int block_i);

char				*my_strndup(char *s, size_t n);
int					my_strcmp(char *s1, char *s2);
char				*ft_strnjoin(char *result, char *str, size_t size);
int					ft_isspace(char c);

t_inner_block_list	*create_inner_block_list(void);
void				add_inner_block(t_inner_block_list *lst,
						t_inner_block *new_node);
void				free_inner_block(t_inner_block_list *lst);

void				signal_default(void);
void				ignore_signal(int signum);
void				set_terminal(int setting);

char				*get_env(char *key, t_env_list *env_list);
int					ft_unset(t_blackhole *blackhole);
int					ft_env(t_blackhole *blackhole);
int					ft_export(t_blackhole *blackhole);
int					ft_pwd(t_blackhole *blackhole);
int					ft_cd(t_blackhole *blackhole);
int					ft_echo(t_blackhole *blackhole, int pipe_i);
int					ft_exit(t_blackhole *blackhole);

void				make_child(t_blackhole *blackhole);

void				execute_command(t_blackhole *blackhole);
int					check_cmd_type(t_inner_block *cur_cmd);
void				execute_builtin(t_blackhole *blackhole,
						int cmd_type, int pipe_i);
int					execute_nbuiltin(t_inner_block_list *cmd_list,
						t_env_list *env_list);

char				*get_next_line(int fd);

char				*get_heredoc_input(char *delimeter);

char				**make_argv(t_inner_block_list *cmd_list);
char				**make_envp(t_env_list *envp_list);
char				*make_cmd_path(t_inner_block_list *cmd_list,
						t_env_list *env_list);

int					parsing_error(t_deque *tokens, t_blackhole *blackhole);
void				write_error(char *type);
void				builtin_error(char *str, char *token);
void				builtin_error2(char *str, char *token, char *str2);

int					set_redir_no_fork(t_inner_block_list *redirect_list);
int					set_cur_block_redir(t_inner_block_list *redirect_list,
						t_child_util *child_util);

int					ft_heredoc(char *delimeter, int fd);

int					err_exit(char *field1, char *field2, int return_value);

void				execute_child(t_blackhole *blackhole, int pipe_i);
void				ft_handle_last_status(
						int last_status, t_blackhole *blackhole);

int					ft_redir_output(int *fd_out, char *file_name);

#endif
