/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:46:33 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/21 14:28:54 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parsed_input(t_block *parsed_input, int pipecnt)
{
	int					idx;
	t_inner_block_list	*cmd_list;
	t_inner_block_list	*redirection_list;

	idx = 0;
	while(idx <= pipecnt)
	{
		cmd_list = parsed_input[idx].cmd_list;
		redirection_list = parsed_input[idx].redirection_list;
		free_inner_block(cmd_list);
		free_inner_block(redirection_list);
		idx++;
	}
	free(parsed_input);
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

char	*remove_double_quote(char *str)
{
	char	*result;
	size_t	len;

	len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (len - 1));
	ft_strlcpy(result, (str + 1), len - 1);
	return (result);
}
char	*rm_quote_ap_env(char *cmd, t_env_list *env_list, int is_heredoc)
{
	char	*temp;
	char	*result;

	if (*cmd == '\'')
		return (remove_single_quote(cmd));
	else if (*cmd == '\"')
	{
		temp = remove_double_quote(cmd);
		if (is_heredoc)
			return (temp);
		result = apply_env(temp, env_list);
		free(temp);
		return (result);
	}
	else
	{
		if (is_heredoc)
			return (ft_strdup(cmd));
		return (apply_env(cmd, env_list));
	}
}
