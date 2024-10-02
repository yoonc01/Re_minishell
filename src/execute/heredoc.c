/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:28:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/02 17:01:31 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc_parent(int signum);

int	ft_heredoc(char *delimeter, int fd)
{
	char	*heredoc_str;
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_str = get_heredoc_input(delimeter);
		write(fd, heredoc_str, ft_strlen(heredoc_str));
		free(heredoc_str);
		exit(0);
	}
	else
	{
		signal(SIGINT, sigint_heredoc_parent);
		waitpid(pid, &status, 0);
		signal_default();
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (1);
		else
			return (0);
	}
}

static void	sigint_heredoc_parent(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

char	*get_heredoc_input(char *delimeter)
{
	char	*line;
	char	*input;
	char	*line_nl;
	char	*input_tmp;

	input = (char *)malloc(sizeof(char));
	if (!input)
		malloc_fail();
	input[0] = 0;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimeter, ft_strlen(delimeter) + 1))
			break ;
		line_nl = ft_strjoin(line, "\n");
		input_tmp = ft_strjoin(input, line_nl);
		free(input);
		input = input_tmp;
		free(line);
		free(line_nl);
	}
	free(delimeter);
	free(line);
	return (input);
}
