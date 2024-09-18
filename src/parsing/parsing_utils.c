/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:46:33 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/18 15:40:04 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (result);
}

char	*remove_double_quote(char *str, t_env_list **env_list)
{
	char	*result;
	char	*removed;
	size_t	len;

	len = ft_strlen(str);
	removed = (char *)malloc(sizeof(char) * (len - 1));
	ft_strlcpy(removed, (str + 1), len - 1);
	result = apply_env(removed, env_list);
	free(removed);
	return (result);
}
