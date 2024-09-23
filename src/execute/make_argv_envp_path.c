/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv_envp_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:37:25 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/23 16:03:26 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**make_argv(t_inner_block_list *cmd_list)
{
	char			**argv;
	t_inner_block	*cur_argv;
	int				argv_i;

	argv_i = 0;
	cur_argv = cmd_list->head;
	argv = (char **)malloc(sizeof(char *)*(cmd_list->size + 1));
	while (argv_i < cmd_list->size)
	{
		argv[argv_i] = ft_strdup(cur_argv->str);
		argv_i++;
		cur_argv = cur_argv->next;
	}
	argv[argv_i] = NULL;
	return(argv);
}

char	**make_envp(t_env_list *envp_list)
{
	// TODO
}

char	*make_cmd_path(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	char	*path_env;
	char	**path_arr;
	char	*slash_cmd;
	int		path_i;
	char	*join_path_cmd;

	path_i = 0;
	path_env = get_env("PATH", env_list);
	path_arr = ft_split(path_env, ':');
	slash_cmd = ft_strjoin("/", cmd_list->head->str);
	while (path_arr[path_i])
	{
		join_path_cmd = ft_strjoin(path_arr[path_i], slash_cmd);
		if (!access(join_path_cmd, X_OK)) // TODO: unset PATH 할 경우 고려
			return (join_path_cmd);
		free(join_path_cmd);
		path_i++;
	}
	free(slash_cmd);
	return (NULL); // TODO: cmd 못 찾았을 경우 현재 디렉토리에서 찾아야 함
}