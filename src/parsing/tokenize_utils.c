/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:10:00 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/30 19:57:16 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
