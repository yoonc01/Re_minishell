/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:46:33 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/18 18:14:33 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_inner_block(t_inner_block **lst)
{
	t_inner_block	*temp_inner_block;

	while (*lst)
	{
		temp_inner_block = (*lst)->next;
		free((*lst)->str);
		free((*lst));
		*lst = temp_inner_block;
	}
}
void	free_parsed_input(t_block *parsed_input, int pipecnt)
{
	int				idx;
	t_inner_block	**cmd_list;
	t_inner_block	**redirection_list;

	idx = 0;
	while(idx <= pipecnt)
	{
		cmd_list = parsed_input[idx].cmd_list;
		redirection_list = parsed_input[idx].redirection_list;
		free_inner_block(cmd_list);
		free_inner_block(redirection_list);
		idx++;
	}
	free(parsed_input->cmd_list);
	free(parsed_input->redirection_list);
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
char	*rm_quote_ap_env(char *cmd, t_env_list **env_list, int is_heredoc)
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
