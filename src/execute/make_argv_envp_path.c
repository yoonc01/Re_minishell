/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv_envp_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:37:25 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/23 11:36:13 by ycho2            ###   ########.fr       */
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

char	**make_path(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	// TODO
}