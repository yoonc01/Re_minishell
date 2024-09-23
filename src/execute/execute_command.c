/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:54:32 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/23 17:21:21 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	execute_nbuiltin(t_inner_block_list *cmd_list, t_env_list *env_list);
static int	check_cmd_type(t_inner_block *cur_cmd);
static int	execute_builtin(t_inner_block_list *cmd_list, t_env_list *env_list, int cmd_type);

void	execute_command(t_env_list *env_list, t_inner_block_list *cmd_list)
{
	t_inner_block	*cur_cmd = cmd_list->head;
	int				exit_code;
	const int	cmd_type = check_cmd_type(cur_cmd);
	
	// if (cmd_type <= 6)
	// {
	// 	exit_code = execute_builtin(cmd_list, env_list, cmd_type);
	// 	exit(1);
	// }
	// else
	{
		execute_nbuiltin(cmd_list, env_list);
		exit(1);
	}
}

static int	check_cmd_type(t_inner_block *cur_cmd)
{
	int	type;
	if (my_strcmp(cur_cmd->str, "echo") == 0)
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
	return(type);
}

static int execute_builtin(t_inner_block_list *cmd_list, t_env_list *env_list, int cmd_type)
{
	if (cmd_type == B_ECHO)
		return (ft_echo(cmd_list));
	else if (cmd_type == B_CD)
		return (ft_cd(cmd_list, env_list));
	else if (cmd_type == B_PWD)
		return (ft_pwd(cmd_list));
	else if (cmd_type == B_EXPORT)
		return (ft_export(cmd_list, env_list));
	else if (cmd_type == B_UNSET)
		return (ft_unset(cmd_list, env_list));
	else if (cmd_type == B_ENV)
		return (ft_env(env_list));
	else if (cmd_type == B_EXIT)
		return (1);
	else
		return (1);
}

static void	execute_nbuiltin(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	char	**argv;
	char	**envp = { NULL};
	char	*path;

	argv = make_argv(cmd_list);
	// printf("%s\n", argv[0]);
	path = make_cmd_path(cmd_list, env_list);
	execve(path, argv, envp);
	// echo -> builtin
	// ls -alR
	// ls
	// -alR
	// echo asdfasdfasdfsadfasdf
}
