/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzamTong.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:17:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/18 18:04:34 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:26:06 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/04 21:57:35 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	if (!dest && !size)
		return (ft_strlen(src));
	dest_len = ft_strlen((const char *)dest);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	else
	{
		while (dest_len + i + 1 < size && src[i])
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[dest_len + i] = 0;
		return (src_len + dest_len);
	}
}

int	my_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	if (*s1 > *s2)
		return (1);
	else
		return (-1);
}
char	*my_strndup(char *s, size_t n)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * (n + 1));
	ft_strlcpy(result, s, n + 1);
	return (result);
}

int	ft_isalnum(int c)
{
	return ((c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || (c >= 48 && c <= 57));
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_isspace(char c)
{
	return (9 <= c && c <= 13 || c == ' ');
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*temp_ptr;

	temp_ptr = (unsigned char *)ptr;
	i = 0;
	while (num > i)
		temp_ptr[i++] = (unsigned char)value;
	return (ptr);
}

void	ft_bzero(void *ptr, size_t size)
{
	ft_memset(ptr, 0, size);
}
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s1_cpy;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	s1_cpy = (char *)malloc((len + 1) * sizeof(char));
	if (!s1_cpy)
		return (NULL);
	while (s1[i])
	{
		s1_cpy[i] = s1[i];
		i++;
	}
	s1_cpy[i] = 0;
	return (s1_cpy);
}
void	*ft_calloc(size_t count, size_t size)
{
	void		*arr;
	size_t		mul_size_cnt;

	mul_size_cnt = count * size;
	if (count != 0 && mul_size_cnt / count != size)
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, count * size);
	return (arr);
}
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


typedef struct s_env_list
{
	char				*env_key;
	char				*env_value;
	struct s_env_list	*next;
}	t_env_list;

t_deque	*create_deque(void);
void	insert_front(t_deque *dq, char *str, t_token_type token_type);
void	insert_rear(t_deque *dq, char *str, t_token_type token_type);
void	delete_front(t_deque *dq);
void	delete_rear(t_deque *dq);
void	malloc_fail(void);
void	argc_err(void);
t_deque	*tokenize(char *input, int *pipecnt);



void	malloc_fail(void)
{
	perror("Failed to allocate memory\n");
	exit(EXIT_FAILURE);
}

void	argc_err(void)
{
	perror("argc error\n");
	exit(EXIT_FAILURE);
}
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

void	process_operator_out(char c, size_t *len, t_token_type *token_type)
{
	if (c == '>')
	{
		*len = 2;
		*token_type = REDIR_APPEND;
	}
	else
	{
		*len = 1;
		*token_type = REDIR_OUT;
	}
}

void	process_operator_in(char c, size_t *len, t_token_type *token_type)
{
	if (c == '<')
	{
		*len = 2;
		*token_type = HEREDOC;
	}
	else
	{
		*len = 1;
		*token_type = REDIR_IN;
	}
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

void	free_inner_block(t_inner_block **lst)
{
	t_inner_block	*temp_inner_block;

	while (*lst)
	{
		temp_inner_block = (*lst)->next;
		free((*lst));
		*lst = temp_inner_block;
	}
}
void	free_parsed_input(t_block *parsed_input, t_deque *tokens, int block_i)
{
	int				idx;
	t_inner_block	**cmd_list;
	t_inner_block	**redirection_list;

	idx = 0;
	while(idx <= block_i)
	{
		cmd_list = parsed_input[idx].cmd_list;
		redirection_list = parsed_input[idx].redirection_list;
		free_inner_block(cmd_list);
		free_inner_block(redirection_list);
		idx++;
	}
	free(parsed_input);
	while (tokens->front != NULL)
		delete_front(tokens);
}

char	*remove_single_quote(char *str)
{
	char	*result;
	size_t	len;

	len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (len - 1));
	ft_strlcpy(result, (str + 1), len - 1);
	free(str);
	return (result);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:29 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/15 19:23:34 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_valid_env_key(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_value(char *str, size_t *idx, t_env_list **env_list)
{
	t_env_list	*temp;
	char		*env_key;

	(*idx)++;
	if (ft_isdigit(str[*idx]))
		return ("");
	while (is_valid_env_key(str[*idx]))
		(*idx)++;
	env_key = my_strndup(str + 1, *idx - 1);
	temp = (*env_list);
	while(temp->next != NULL)
	{
		if (my_strcmp(env_key, temp->env_key) == 0)
			return (temp->env_value);
		temp = temp->next;
	}
	return ("");
}

char	*ft_strnjoin(char *result, char *str, size_t size)
{
	char	*new_result;

	new_result = (char *)malloc(sizeof(char) * (ft_strlen(result) + size + 1));
	ft_strlcpy(new_result, result, ft_strlen(result) + 1);
	ft_strlcat(new_result, str, (ft_strlen(result) + size + 1));
	free(result);
	return (new_result);
}
char	*apply_env(char *str, t_env_list **env_list)
{
	size_t	idx;
	char	*result;
	char	*env_value;

	result = ft_strdup("");
	idx = 0;
	while (1)
	{
		if ((str[idx] == '$' && is_valid_env_key(str[idx + 1])) || str[idx] == '\0')
		{
			result = ft_strnjoin(result, str, idx);
			str = str + idx;
			idx = 0;
			if (str[idx] == '\0')
				return (result);
			env_value = get_env_value(str, &idx, env_list);
			result = ft_strnjoin(result, env_value, ft_strlen(env_value));
			str = str + idx;
			idx = 0;
		}
		else
			idx++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:32:00 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/29 16:34:24 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		count_words(char const *s, char c);
static char		*sep_words(char const *s, int start, int end);
static int		save_words(char const *s, char c, char **split);

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	save_words(s, c, split);
	return (split);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	cnt;
	int	flag;

	i = 0;
	cnt = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			cnt++;
		}
		else if (s[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	return (cnt);
}

static char	*sep_words(char const *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (0);
	while (i < end - start)
	{
		word[i] = s[i + start];
		i++;
	}
	word[i] = 0;
	return (word);
}

static int	save_words(char const *s, char c, char **split)
{
	size_t		i;
	long long	start;
	size_t		nth_word;

	start = -1;
	nth_word = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start == -1)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start != -1)
		{
			split[nth_word] = sep_words(s, start, i);
			if (!split[nth_word])
				return (0);
			start = -1;
			nth_word++;
		}
		i++;
	}
	split[nth_word] = 0;
	return (1);
}

void	split_free(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


			// temp = ft_calloc((ft_strlen(str) + ft_strlen(env_value) + 1), sizeof(char));
			// ft_strlcpy(temp, result, idx + 1);
			// ft_strlcat(temp, env_value, ft_strlen(env_value) + 1);
			// free(result);
			// result = temp;
			// idx = idx + ft_strlen(env_value);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/15 19:28:57 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void add_inner_block(t_inner_block **lst, t_inner_block *new_node)
{
	t_inner_block	*current_node;
	
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current_node = *lst;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}

int	put_block_cmd(t_deque *tokens, t_block parsed_input, t_env_list **env_list)
{
	t_inner_block	*new_node;
	t_inner_block	*current_node;
	t_inner_block	**cmd_list;
	char			*str;

	cmd_list = parsed_input.cmd_list;
	new_node = (t_inner_block *)malloc(sizeof(t_inner_block));
	str = tokens->front->str;
	if (*str == '\'')
		str = remove_single_quote(str);
	else
		str = apply_env(str, env_list);
	new_node->str = str;
	new_node->next = NULL;
	add_inner_block(cmd_list, new_node);
	delete_front(tokens);
	return (1);
}

int	put_block_redirect(t_deque *tokens, t_block parsed_input)
//TODO error 시 누수 확인 
{
	t_inner_block	*new_node_redirection;
	t_inner_block	*new_node_file;
	t_inner_block	*current_node;
	t_inner_block	**redirection_list;

	redirection_list = parsed_input.redirection_list;
	if (tokens->front->next == NULL || tokens->front->next->token_type != WORD)
		return (0);
	new_node_redirection = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_file = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_redirection->str = ft_strdup(tokens->front->str);
	new_node_redirection->next = new_node_file;
	delete_front(tokens);
	new_node_file->str = ft_strdup(tokens->front->str);
	new_node_file->next = NULL;
	delete_front(tokens);
	add_inner_block(redirection_list, new_node_redirection);
	return (1);
}

t_block	*parsing_block(t_deque *tokens, int pipecnt, t_env_list **env_list)
{
	t_block	*parsed_input;
	int		block_i;
	int		grammar_valid;

	parsed_input = (t_block *)ft_calloc((pipecnt + 1), sizeof(t_block));
	block_i = 0;
	while(block_i < pipecnt + 1)
	{
		parsed_input[block_i].cmd_list = (t_inner_block **)calloc(1, sizeof(t_inner_block *));
		parsed_input[block_i].redirection_list = (t_inner_block **)calloc(1, sizeof(t_inner_block *));
		block_i++;
	}
	block_i = 0;
	grammar_valid = 1;
	while (tokens->front != NULL && grammar_valid)
	{
		if (tokens->front->token_type == WORD)
			grammar_valid = put_block_cmd(tokens, parsed_input[block_i], env_list);
		else if (tokens->front->token_type == PIPE)
		{
			if (tokens->front->next == NULL)
				grammar_valid = 0;
			block_i++;
			delete_front(tokens);
		}
		else
			grammar_valid = put_block_redirect(tokens, parsed_input[block_i]);
	}
	if (grammar_valid == 0)
		free_parsed_input(parsed_input, tokens, block_i);
	return (parsed_input);
}

t_block	*parsing(char *input, t_env_list **env_list)
{
	t_deque	*tokens;
	int		pipecnt;
	t_block	*parsed_input;

	pipecnt = 0;
	tokens = tokenize(input, &pipecnt);
	if (tokens == NULL)
		return (0);
	parsed_input = parsing_block(tokens, pipecnt, env_list);
	return (parsed_input);
}


static int check_env_add(char *env_key)
{
	if (env_key[0] >= '0' && env_key[0] <= '9')
		return (0);
	else
	{
		while (*env_key != 0)
		{
			if (!(ft_isalnum(*env_key)||*env_key=='_'))
				return (0);
			env_key++;
		}
	}
	return (1);
}

int add_new_list(char *env, t_env_list **env_list)
{
	t_env_list	*new_node;
	t_env_list	*tmp_node;
	char		**splited_env;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	splited_env = ft_split(env, '=');
	if (check_env_add(splited_env[0]) == 0)
		return (0);
	new_node->env_key = splited_env[0];
	new_node->env_value = splited_env[1];
	new_node->next = NULL;
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		tmp_node = *env_list;
		while (tmp_node->next != NULL)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
	}
	return (1);
}

static void	init_env_list(char **env, t_env_list **env_list)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		add_new_list(env[i], env_list);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	ac = 0;
	av = NULL;
	t_env_list *env_list;
	env_list = NULL;
	init_env_list(env, &env_list);
	int	idx = 0;
	int pipecnt = 0;
	char *input = "Hyoyoon \"cat\" $TERM$TERM > out | hello";
	t_block	*parsed_input = parsing(input, &env_list);
	while (parsed_input[idx].cmd_list != NULL || parsed_input[idx].redirection_list != NULL)
	{
		t_inner_block **cmd_list = parsed_input[idx].cmd_list;
		t_inner_block **redirection_list = parsed_input[idx].redirection_list;
		t_inner_block *temp = *cmd_list;
		while (temp != NULL)
		{
			printf("%s\n", temp->str);
			temp = temp->next;
		}
		temp = *redirection_list;
		while (temp != NULL)
		{
			printf("%s\n", temp->str);
			temp = temp->next;
		}
		printf("\n");
		idx++;
	}
}