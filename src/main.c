/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 15:38:48 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_list(char **env, t_env_list *env_list)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		add_env(env[i], env_list);
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
	int		pipe_idx = 0;
	int		pipecnt;

	command = readline("minishell$ \033[s");
	if(command)
	{
		add_history(command);
		t_block	*parsed_input = parsing(command, &pipecnt, env_list);
		make_child(pipecnt, parsed_input, env_list);
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

	// atexit(check_leak);
	if (ac != 1)
		argc_err();
	set_signals();
	set_terminal();
	env_list = create_env_list();
	init_env_list(env, env_list);
	while(rl_gets(env_list));	
	free_env_list(env_list);
}
