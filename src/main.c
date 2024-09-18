/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/18 18:43:59 by ycho2            ###   ########.fr       */
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
void	check_leak(void)
{
	system("leaks -q minishell");
}

static char	*rl_gets(t_env_list *env_list)
{
	char	*command;
	int			pipe_idx = 0;
	int			pipecnt;

	command = readline("minishell$ \033[s");
	if(command && *command)
	{
		add_history(command);
		t_block	*parsed_input = parsing(command, &pipecnt, &env_list);
		while (pipe_idx <= pipecnt)
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
		free_parsed_input(parsed_input, pipecnt);
		free(command);
	}
	else
	{
		printf("\033[u\033[1B\033[1Aexit\n");
		exit(0);
	}
	return(command);
}

int	main(int ac, char **av, char **env)
{
	t_env_list	*env_list;
	int			pipe_idx = 0;
	int			pipecnt;

	atexit(check_leak);
	if (ac != 1)
		argc_err();
	set_signals();
	set_terminal();
	env_list = NULL;
	init_env_list(env, &env_list);
	while(rl_gets(env_list));	
	free_env_list(&env_list);
}
