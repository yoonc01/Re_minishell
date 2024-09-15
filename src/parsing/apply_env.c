/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:29 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/15 18:47:36 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_env_key(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_value(char **str, t_env_list **env_list)
{
	t_env_list	*temp;
	char		*env_key;
	char		*key_start;

	(*str)++;
	key_start = *str;
	if (ft_isdigit(*str))
		return ("");
	while (is_valid_env_key(**str))
		(*str)++;
	env_key = my_strndup(key_start, *str - key_start);
	temp = (*env_list);
	while(temp->next != NULL)
	{
		if (ft_strncmp(env_key, temp->env_key, ft_strlen(env_key)) == 0)
			return (temp->env_value);
		temp = temp->next;
	}
	return ("");
}
char	*apply_env(char *str, t_env_list **env_list)
{
	char	*dst;
	char	*temp;
	char	*result;
	char	*env_value;

	result = ft_strdup(str);
	dst = result;
	while (*str != '\0')
	{
		if (*str == '$' && is_valid_env_key(*(str + 1)))
		{
			env_value = get_env_value(&str, env_list);
			temp = ft_calloc((ft_strlen(result) + ft_strlen(env_value) + 1), sizeof(char));
			ft_strlcpy(temp, result, dst - result + 1);
			ft_strlcat(temp, env_value, ft_strlen(env_value) + 1);
			free(result);
			result = temp;
			dst = result + ft_strlen(result);
		}
		else
			*dst++ = *str++;
	}
	*dst = '\0';
	return (result);
}
