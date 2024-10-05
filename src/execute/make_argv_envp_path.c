/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv_envp_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:37:25 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/05 13:44:56 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_argv(t_inner_block_list *cmd_list)
{
	char			**argv;
	t_inner_block	*cur_argv;
	int				argv_i;

	argv_i = 0;
	cur_argv = cmd_list->head;
	argv = (char **)malloc(sizeof(char *) * (cmd_list->size + 1));
	if (argv == NULL)
		malloc_fail();
	while (argv_i < cmd_list->size)
	{
		argv[argv_i] = ft_strdup(cur_argv->str);
		argv_i++;
		cur_argv = cur_argv->next;
	}
	argv[argv_i] = NULL;
	return (argv);
}

char	**make_envp(t_env_list *envp_list)
{
	char		**env_arr;
	int			env_i;
	t_env_node	*cur_env;
	char		*tmp_str;

	env_i = 0;
	env_arr = (char **)malloc((envp_list->size + 1) * sizeof(char *));
	if (env_arr == NULL)
		malloc_fail();
	cur_env = envp_list->head;
	while (env_i < envp_list->size)
	{
		tmp_str = ft_strjoin(cur_env->env_key, "=");
		env_arr[env_i] = ft_strjoin(tmp_str, cur_env->env_value);
		free(tmp_str);
		cur_env = cur_env->next;
		env_i++;
	}
	return (env_arr);
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
	slash_cmd = ft_strjoin("/", cmd_list->head->str);
	path_arr = ft_split(path_env, ':');
	while (path_arr[path_i])
	{
		join_path_cmd = ft_strjoin(path_arr[path_i], slash_cmd);
		free(path_arr[path_i]);
		if (!access(join_path_cmd, X_OK))
		{
			free(slash_cmd);
			return (join_path_cmd);
		}
		free(join_path_cmd);
		path_i++;
	}
	join_path_cmd = ft_strjoin(".", slash_cmd);
	free(slash_cmd);
	return (join_path_cmd);
}
