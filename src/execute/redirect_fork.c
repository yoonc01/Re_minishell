/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:10:33 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/03 14:04:59 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_append(int *fd_out, char *file_name);
static int	ft_redir_heredoc(int *fd_in, char *delimeter);
static int	ft_redir_input(int *fd_in, char *file_name);
static int	ft_set_child_redir_word(int *flag, int *fd_in,
				int *fd_out, t_inner_block *cur_redir);

int	set_cur_block_redir(t_inner_block_list *redirect_list,
				t_child_util *child_util)
{
	int				fd_out;
	int				fd_in;
	int				flag;
	t_inner_block	*cur_redir;

	fd_in = -1;
	fd_out = -1;
	flag = 0;
	cur_redir = redirect_list->head;
	while (cur_redir)
	{
		if (cur_redir->type == WORD)
		{
			if (ft_set_child_redir_word(&flag, &fd_in, &fd_out, cur_redir) == 1)
				return (1);
		}
		else
			flag = cur_redir->type;
		cur_redir = cur_redir->next;
	}
	if (fd_in >= 0)
		child_util->childfd[0] = fd_in;
	if (fd_out >= 0)
		child_util->childfd[1] = fd_out;
	return (0);
}

static int	ft_set_child_redir_word(int *flag, int *fd_in,
	int *fd_out, t_inner_block *cur_redir)
{
	if (*flag == REDIR_IN)
	{
		if (ft_redir_input(fd_in, cur_redir->str))
			return (1);
	}
	else if (*flag == HEREDOC)
	{
		if (ft_redir_heredoc(fd_in, cur_redir->str))
			return (1);
	}
	else if (*flag == REDIR_OUT)
	{
		if (ft_redir_output(fd_out, cur_redir->str))
			return (1);
	}
	else if (*flag == REDIR_APPEND)
	{
		if (ft_redir_append(fd_out, cur_redir->str))
			return (1);
	}
	return (0);
}

static int	ft_redir_append(int *fd_out, char *file_name)
{
	if (*fd_out > 0)
		close(*fd_out);
	*fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out < 0)
		return (err_exit(file_name, strerror(errno), 1));
	else
		return (0);
}

static int	ft_redir_input(int *fd_in, char *file_name)
{
	if (*fd_in > 0)
		close(*fd_in);
	*fd_in = open(file_name, O_RDONLY, 0);
	if (*fd_in < 0)
		return (err_exit(file_name, strerror(errno), 1));
	else
		return (0);
}

static int	ft_redir_heredoc(int *fd_in, char *delimeter)
{
	if (*fd_in > 0)
		close(*fd_in);
	*fd_in = open("/var/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (ft_heredoc(delimeter, *fd_in) == 1)
		return (1);
	close(*fd_in);
	*fd_in = open("/var/tmp/tmp.txt", O_RDONLY);
	return (0);
}
