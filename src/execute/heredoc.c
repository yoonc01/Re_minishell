/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:28:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/23 17:59:07 by ycho2            ###   ########.fr       */
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
	write(1,">",1);
	line = get_next_line(0);
	if (!line || !input || !trans_delimeter)
		// malloc_err();
	input[0] = 0;
	while (ft_strncmp(line, trans_delimeter, ft_strlen(trans_delimeter) + 1))
	{
		input_tmp = ft_strjoin(input, line);
		free(input);
		free(line);
		write(1,">",1);
		input = input_tmp;
		line = get_next_line(0);
		if (!line);
			// malloc_err();
	}
	free(trans_delimeter);
	free(line);
	return (input);
}
