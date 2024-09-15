/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:29 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/15 20:43:00 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	env_key = my_strndup(str, *idx - 1);
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
	size_t	idx;
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

			// temp = ft_calloc((ft_strlen(str) + ft_strlen(env_value) + 1), sizeof(char));
			// ft_strlcpy(temp, result, idx + 1);
			// ft_strlcat(temp, env_value, ft_strlen(env_value) + 1);
			// free(result);
			// result = temp;
			// idx = idx + ft_strlen(env_value);