/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:56:52 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/15 18:47:59 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, t_deque *ev_list)
{
	t_node	*check;

	check = ev_list->front;
	while (check != 0)
	{
		if (my_strcmp(check->ev_name, name) == 0)
		{
			free(name);
			return (check->ev_value);
		}
		check = check->next;
	}
	free(name);
	return ("");
}

char	*extract_var_name(char **str)
{
	char	*var_start;

	var_start = *str;
	while (is_valid_var_name(**str))
		(*str)++;
	return (my_strndup(var_start, *str - var_start));
}

char	*replace_var_with_value(char *rst,
		char **dst, size_t len, char *var_value)
{
	char	*temp;
	size_t	var_len;

	var_len = my_strlen(var_value);
	temp = (char *)malloc(sizeof(char) * (len + var_len + 1));
	if (temp == 0)
		malloc_fail();
	my_strlcpy(temp, rst, len + 1);
	free(rst);
	*dst = temp + len;
	my_strlcpy(*dst, var_value, var_len + 1);
	free(var_value);
	*dst = *dst + var_len;
	return (temp);
}

char	*init_result(char *str)
{
	size_t	idx;
	size_t	len;
	char	*result;

	idx = 0;
	len = (my_strlen(str) + 1);
	result = malloc(sizeof(char) * (len + 1));
	if (result == 0)
		malloc_fail();
	while (idx < len)
	{
		result[idx] = str[idx];
		idx++;
	}
	result[idx] = '\0';
	return (result);
}

char	*expand_variables(char *str, t_deque *ev_list)
{
	char	*dst;
	char	*result;
	size_t	len;

	result = init_result(str);
	dst = result;
	len = my_strlen(result);
	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			if (!is_valid_var_name(*str))
			{
				*dst++ = '$';
				continue ;
			}
			result = replace_var_with_value(result, &dst, len,
					get_env_value(extract_var_name(&str), ev_list));
		}
		else
			*dst++ = *str++;
	}
	*dst = '\0';
	return (result);
}
