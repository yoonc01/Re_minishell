/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/16 17:14:24 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_list(char **env, t_env_list **env_list)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		add_new_list(env[i], env_list);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env_list	*env_list;
	int			pipe_idx;
	ac;
	av;
	env;

	env_list = NULL;
	init_env_list(env, &env_list);
	char *input = "Hyoyoon \"cat\" $TERM$TERM > out | hello";
	t_block	*parsed_input = parsing(input, &env_list);
	while (parsed_input[pipe_idx].cmd_list != NULL || parsed_input[pipe_idx].redirection_list != NULL)
	{
		t_inner_block **cmd_list = parsed_input[pipe_idx].cmd_list;
		t_inner_block **redirection_list = parsed_input[pipe_idx].redirection_list;
		t_inner_block *temp = *cmd_list;
		while (temp != NULL)
		{
			printf("%s\n", temp->str);
			temp = temp->next;
		}
		temp = *redirection_list;
		while (temp != NULL)
		{
			printf("%s\n", temp->str);
			temp = temp->next;
		}
		printf("\n");
		pipe_idx++;
	}
}
