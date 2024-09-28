/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:54:32 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/28 17:39:31 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	execute_command(int pipecnt, t_block *parsed_input, t_env_list *env_list, int *exit_code)
{
	int	head_cmd_type = check_cmd_type(parsed_input->cmd_list->head);
	int tmp_std_in;
	int tmp_std_out;

	if (pipecnt == 0 && head_cmd_type <= 6)
		{
			printf("%d\n", head_cmd_type); //TODO for debug
			tmp_std_in = dup(STDIN_FILENO);// restore in out default fd
			tmp_std_out = dup(STDOUT_FILENO);
			set_redir_solo(parsed_input->redirection_list);
			*exit_code = execute_builtin(parsed_input->cmd_list, env_list, head_cmd_type);
			dup2(tmp_std_in, STDIN_FILENO);
			dup2(tmp_std_out, STDOUT_FILENO);
			printf("%d %d\n", head_cmd_type, parsed_input->cmd_list->size); //TODO for debug
		}
	else
		make_child(pipecnt, parsed_input, env_list);
}

int	check_cmd_type(t_inner_block *cur_cmd)
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

int execute_builtin(t_inner_block_list *cmd_list, t_env_list *env_list, int cmd_type)
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
		return (ft_exit(cmd_list));
}

void	execute_nbuiltin(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	char	**argv;
	char	**envp = { NULL};
	char	*path;

	argv = make_argv(cmd_list);
	path = make_cmd_path(cmd_list, env_list);
	envp = make_envp(env_list);
	execve(path, argv, envp);
}
