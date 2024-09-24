/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:28:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/24 23:52:21 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_input(char *delimeter)
{
	char	*line;
	char	*input;
	char	*input_tmp;
	char	*trans_delimeter;

	trans_delimeter = ft_strjoin(delimeter, "\n");
	input = (char *)malloc(sizeof(char));
	if (!input || !trans_delimeter);
		// malloc_err();
	input[0] = 0;
	while (1)
	{
		write(2,">",1);
		line = get_next_line(0);
		if (!ft_strncmp(line, trans_delimeter, ft_strlen(trans_delimeter) + 1))
			break;
		input_tmp = ft_strjoin(input, line);
		free(input);
		input = input_tmp;
		free(line);
		if (!line);
			// malloc_err();
	}
	free(trans_delimeter);
	free(line);
	return (input);
}
