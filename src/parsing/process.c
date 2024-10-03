/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:38:59 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 12:01:05 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quote(char **str, char c)
{
	char	*result;
	size_t	len;

	len = 1;
	while ((*str)[len] != c && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\0')
		return (NULL);
	result = (char *)malloc(sizeof(char) * len);
	if (result == NULL)
		malloc_fail();
	ft_strlcpy(result, ((*str) + 1), len);
	*str = *str + len + 1;
	return (result);
}

static char	*extract_word(char **str)
{
	char	*result;
	size_t	len;

	len = 0;
	while ((*str)[len] != '\0' && (*str)[len] != '\'' && (*str)[len] != '\"')
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		malloc_fail();
	ft_strlcpy(result, (*str), len + 1);
	*str = *str + len;
	return (result);
}

static char	*rm_quote_ap_env(char **cmd, t_blackhole *blackhole)
{
	char	*temp;
	char	*result;

	if (**cmd == '\'')
		return (remove_quote(cmd, '\''));
	else if (**cmd == '\"')
	{
		temp = remove_quote(cmd, '\"');
		if (temp == NULL)
		{
			write_error("quote");
			blackhole->exit_code = 258;
			return (NULL);
		}
		result = apply_env(temp, blackhole);
		free(temp);
		return (result);
	}
	else
	{
		temp = extract_word(cmd);
		result = apply_env(temp, blackhole);
		free(temp);
		return (result);
	}
}

char	*process(char *cmd, t_blackhole *blackhole, int is_heredoc)
{
	char	*result;
	char	*attach;

	if (is_heredoc)
		return (ft_strdup(cmd));
	result = ft_strdup("");
	while (*cmd != '\0')
	{
		attach = rm_quote_ap_env(&cmd, blackhole);
		if (attach == NULL)
			return (NULL);
		result = ft_strnjoin(result, attach, ft_strlen(attach));
		free(attach);
	}
	return (result);
}
