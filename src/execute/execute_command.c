/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:54:32 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/02 19:32:25 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_blackhole *blackhole)
{
	int		head_cmd_type;
	int		tmp_std_in;
	int		tmp_std_out;
	int		red_err;

	head_cmd_type = check_cmd_type(blackhole->parsed_input->cmd_list->head);
	if (blackhole->pipe_cnt == 0 && head_cmd_type <= 7)
	{
		tmp_std_in = dup(STDIN_FILENO);
		tmp_std_out = dup(STDOUT_FILENO);
		red_err = set_redir_no_fork(blackhole->parsed_input->redirection_list);
		if (red_err == 1)
		{
			blackhole->exit_code = 1;
			return ;
		}
		if (head_cmd_type == B_NULL)
			blackhole->exit_code = 0;
		else
			execute_builtin(blackhole, head_cmd_type);
		dup2(tmp_std_in, STDIN_FILENO);
		dup2(tmp_std_out, STDOUT_FILENO);
	}
	else
		make_child(blackhole);
}

int	check_cmd_type(t_inner_block *cur_cmd)
{
	int	type;

	if (cur_cmd == NULL)
		type = B_NULL;
	else if (my_strcmp(cur_cmd->str, "echo") == 0)
		type = B_ECHO;
	else if (my_strcmp(cur_cmd->str, "cd") == 0)
		type = B_CD;
	else if (my_strcmp(cur_cmd->str, "pwd") == 0)
		type = B_PWD;
	else if (my_strcmp(cur_cmd->str, "export") == 0)
		type = B_EXPORT;
	else if (my_strcmp(cur_cmd->str, "unset") == 0)
		type = B_UNSET;
	else if (my_strcmp(cur_cmd->str, "env") == 0)
		type = B_ENV;
	else if (my_strcmp(cur_cmd->str, "exit") == 0)
		type = B_EXIT;
	else
		type = NONBUILTIN;
	return (type);
}

void	execute_builtin(t_blackhole *blackhole, int cmd_type)
{
	if (cmd_type == B_ECHO)
		blackhole->exit_code = ft_echo(blackhole);
	else if (cmd_type == B_CD)
		blackhole->exit_code = ft_cd(blackhole);
	else if (cmd_type == B_PWD)
		blackhole->exit_code = ft_pwd();
	else if (cmd_type == B_EXPORT)
		blackhole->exit_code = ft_export(blackhole);
	else if (cmd_type == B_UNSET)
		blackhole->exit_code = ft_unset(blackhole);
	else if (cmd_type == B_ENV)
		blackhole->exit_code = ft_env(blackhole);
	else if (cmd_type == B_EXIT)
		blackhole->exit_code = ft_exit(blackhole);
}

int	execute_nbuiltin(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	char	**argv;
	char	**envp;
	char	*path;

	argv = make_argv(cmd_list);
	envp = make_envp(env_list);
	path = make_cmd_path(cmd_list, env_list);
	execve(path, argv, envp);
	if (errno == ENOENT)
	{
		err_exit(argv[0], "command not found");
		return (127);
	}
	err_exit(argv[0], strerror(errno));
	return (EXIT_FAILURE);
}
