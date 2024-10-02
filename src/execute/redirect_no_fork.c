/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_no_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:24:51 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/03 06:14:18 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_in_nfork(t_inner_block *redirect_block, int flag);
static int	redir_out_nfork(t_inner_block *redirect_block, int flag);
static void	redir_out_nfork_util(t_inner_block **curr_redir, int *flag);

// int	set_redir_no_fork(t_inner_block_list *redirect_list)
// {
// 	int				flag;
// 	t_inner_block	*curr_redir;
// 	int				redir_err;

// 	flag = 0;
// 	curr_redir = redirect_list->head;
// 	while (curr_redir)
// 	{
// 		printf("%s %d\n", curr_redir->str, curr_redir->type);
// 		if (curr_redir->type == WORD && flag <= 3)
// 		{
// 			redir_err = redir_in_nfork(curr_redir, flag);
// 			if (redir_err == 1)
// 				return (1);
// 		}
// 		else
// 			flag = curr_redir->type;
// 		curr_redir = curr_redir->next;
// 	}
// 	flag = 0;
// 	curr_redir = redirect_list->head;
// 	while (curr_redir)
// 		redir_out_nfork_util(&curr_redir, &flag);
// 	return (0);
// }

int	set_redir_no_fork(t_inner_block_list *redir_list)
{
	int				flag;
	t_inner_block	*curr_redir;
	int				redir_err;
	t_child_util	child_util;

	flag = 0;
	child_util.pipe_i = 0;
	child_util.pipecnt = 0;
	child_util.childfd[0] = STDIN_FILENO;
	child_util.childfd[1] = STDOUT_FILENO;
	if (set_child_redir(redir_list, &child_util))
		return (1);
	dup2(child_util.childfd[0], STDIN_FILENO);
	dup2(child_util.childfd[1], STDOUT_FILENO);
	return (0);
}

static void	redir_out_nfork_util(t_inner_block **curr_redir, int *flag)
{
	if ((*curr_redir)->type == WORD && *flag >= 4)
		redir_out_nfork(*curr_redir, *flag);
	else
		*flag = (*curr_redir)->type;
	*curr_redir = (*curr_redir)->next;
}

static int	redir_in_nfork(t_inner_block *redirect_block, int flag)
{
	int		fd;
	int		heredoc_sigint;

	if (flag == REDIR_IN)
	{
		fd = open(redirect_block->str, O_RDONLY, 0);
		if (fd < 0)
		{
			err_exit(redirect_block->str, strerror(errno));
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		fd = open("/var/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		heredoc_sigint = ft_heredoc(redirect_block->str, fd);
		if (heredoc_sigint == 1)
			return (1);
		fd = open("/var/tmp/tmp.txt", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	redir_out_nfork(t_inner_block *redirect_block, int flag)
{
	int	fd;

	if (flag == REDIR_OUT)
	{
		fd = open(redirect_block->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			err_exit(redirect_block->str, strerror(errno));
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (flag == REDIR_APPEND)
	{
		fd = open(redirect_block->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			err_exit(redirect_block->str, strerror(errno));
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
