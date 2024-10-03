/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:29 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 11:13:14 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char *token_word, size_t *idx,
				t_blackhole *blackhole)
{
	t_env_node	*temp;
	char		*env_key;

	(*idx)++;
	if (token_word[(*idx)++] == '?')
		return (ft_itoa(blackhole->exit_code));
	if (ft_isdigit(token_word[(*idx)]))
		return (ft_strdup(""));
	while (is_valid_env_key(token_word[*idx]))
		(*idx)++;
	env_key = my_strndup(token_word + 1, *idx - 1);
	temp = blackhole->env_list->head;
	while (temp != NULL)
	{
		if (my_strcmp(env_key, temp->env_key) == 0)
		{
			free(env_key);
			return (ft_strdup(temp->env_value));
		}
		temp = temp->next;
	}
	free(env_key);
	return (ft_strdup(""));
}

static int	check_condition(char *token_word, size_t token_word_i)
{
	if (token_word[token_word_i] == '$')
	{
		if (token_word[token_word_i + 1] == '?')
			return (1);
		else if (is_valid_env_key(token_word[token_word_i + 1]))
			return (1);
		return (0);
	}
	else if (token_word[token_word_i] == '\0')
		return (1);
	return (0);
}

char	*apply_env(char *token_word, t_blackhole *blackhole)
{
	size_t	token_word_i;
	char	*env_applied;
	char	*env_value;

	env_applied = ft_strdup("");
	token_word_i = 0;
	while (1)
	{
		if (check_condition(token_word, token_word_i))
		{
			env_applied = ft_strnjoin(env_applied, token_word, token_word_i);
			token_word = token_word + token_word_i;
			token_word_i = 0;
			if (token_word[token_word_i] == '\0')
				return (env_applied);
			env_value = get_env_value(token_word, &token_word_i, blackhole);
			env_applied = ft_strnjoin(env_applied,
					env_value, ft_strlen(env_value));
			free(env_value);
			token_word = token_word + token_word_i;
			token_word_i = 0;
		}
		else
			token_word_i++;
	}
}
