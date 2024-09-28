/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:33:25 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/28 16:24:52 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_inner_block_list *cmd_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		malloc_fail();
	write(STDIN_FILENO, cwd, ft_strlen(cwd));
	write(STDIN_FILENO, "\n", 1);
	free(cwd);
    return (EXIT_SUCCESS);	
}