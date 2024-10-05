/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:54:32 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/05 14:23:38 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isdirectory(char *path);

void	execute_command(t_blackhole *blackhole)
{
	int		head_cmd_type;
	int		tmp_std_in;
	int		tmp_std_out;

	head_cmd_type = check_cmd_type(blackhole->parsed_input->cmd_list->head);
	if (blackhole->pipe_cnt == 0 && head_cmd_type <= 7)
	{
		tmp_std_in = dup(STDIN_FILENO);
		tmp_std_out = dup(STDOUT_FILENO);
		if (set_redir_no_fork(blackhole->parsed_input->redirection_list) == 1)
		{
			blackhole->exit_code = 1;
			return ;
		}
		if (head_cmd_type == B_NULL)
			blackhole->exit_code = 0;
		else
			execute_builtin(blackhole, head_cmd_type, 0);
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

void	execute_builtin(t_blackhole *blackhole, int cmd_type, int pipe_i)
{
	if (cmd_type == B_ECHO)
		blackhole->exit_code = ft_echo(blackhole, pipe_i);
	else if (cmd_type == B_CD)
		blackhole->exit_code = ft_cd(blackhole);
	else if (cmd_type == B_PWD)
		blackhole->exit_code = ft_pwd(blackhole);
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
	char		**argv;
	char		**envp;
	char		*path;
	struct stat	path_stat;

	envp = make_envp(env_list);
	argv = make_argv(cmd_list);
	if (isdirectory(cmd_list->head->str))
	{
		if (stat(cmd_list->head->str, &path_stat) != 0)
			return (err_exit(cmd_list->head->str,
					"No such file or directory", 127));
		if (!(path_stat.st_mode & S_IXUSR))
			return (err_exit(cmd_list->head->str, "Permission denied", 126));
		if ((path_stat.st_mode & 0170000) == 0040000)
			return (err_exit(cmd_list->head->str, "is a directory", 126));
		execve(cmd_list->head->str, argv, envp);
	}
	path = make_cmd_path(cmd_list, env_list);
	if (!access(path, X_OK) && stat(path, &path_stat) == 0
		&& S_ISREG(path_stat.st_mode))
		execve(path, argv, envp);
	return (err_exit(argv[0], "command not found", 127));
}

static int	isdirectory(char *path)
{
	if (ft_strncmp(path, "./", 2) == 0 || ft_strncmp(path, "/", 1) == 0)
		return (1);
	return (0);
}
