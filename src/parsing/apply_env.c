/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:29 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/21 15:50:22 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경 변수 키 값 str에 받아와서 value 반환
// $1 $2 -> $뒤에 숫자 오는 경우 빈문자열 받환
char	*get_env_value(char *token_word, size_t *idx, t_env_list *env_list)
{
	t_env_node	*temp;
	char		*env_key;

	// 현재 인덱스 $이므로 하나 넘겨줌
	(*idx)++;
	// 환경변수 key 값 첫번째가 숫자인지 확인
	if (ft_isdigit(token_word[*idx]))
	{
		(*idx)++;
		return ("");
	}
	// 키 값이 적절한지 확인하면서 인덱스 밀어주기
	while (is_valid_env_key(token_word[*idx]))
		(*idx)++;
	env_key = my_strndup(token_word+1, *idx - 1);
	temp = env_list->head;
	while(temp->next != NULL)
	{
		if (my_strcmp(env_key, temp->env_key) == 0)
		{
			free(env_key);
			return (temp->env_value);
		}
		temp = temp->next;
	}
	// env_list 끝까지 탐색했는데 못찾았을 경우 빈 문자열 리턴
	free(env_key);
	return ("");
}


// WORD 토큰에 환경변수 적용하기
// WORD에 들어있는 환경변수 키 값이 적절한지 1차로 확인 후 밸류 문자열 받아와서 넣어준다 아니면 빈 문자열 넣어준다
char	*apply_env(char *token_word, t_env_list *env_list)
{
	size_t	token_word_i;
	char	*env_applied;
	char	*env_value;

	env_applied = ft_strdup("");
	token_word_i = 0;
	while (1)
	{
		if ((token_word[token_word_i] == '$' && is_valid_env_key(token_word[token_word_i + 1])) || token_word[token_word_i] == '\0')
		{
			//환경 변수 시작 또는 빈문자열 나오면 현재 인덱스 까지 값을 일단 env_applied에 저장해주기
			env_applied = ft_strnjoin(env_applied, token_word, token_word_i);
			token_word = token_word + token_word_i;
			token_word_i = 0;
			if (token_word[token_word_i] == '\0')
				return (env_applied);
			env_value = get_env_value(token_word, &token_word_i, env_list);
			env_applied = ft_strnjoin(env_applied, env_value, ft_strlen(env_value));
			token_word  += token_word_i;
			token_word_i = 0;
		}
		else
		// 환경변수 시작하거나 빈문자열 나올 때 까지 인덱스 밀어줌
			token_word_i++;
	}
}

			// temp = ft_calloc((ft_strlen(str) + ft_strlen(env_value) + 1), sizeof(char));
			// ft_strlcpy(temp, env_applied, idx + 1);
			// ft_strlcat(temp, env_value, ft_strlen(env_value) + 1);
			// free(env_applied);
			// env_applied = temp;
			// idx = idx + ft_strlen(env_value);