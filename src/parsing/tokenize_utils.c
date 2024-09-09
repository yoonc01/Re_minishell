/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:10:00 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/09 14:18:47 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_operator_out(char c, int *len, t_token_type *token_type)
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

void	process_operator_in(char c, int *len, t_token_type *token_type)
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