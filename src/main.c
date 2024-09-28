/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/28 16:37:01 by hyoyoon          ###   ########.fr       */
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
static char	*rl_gets(t_env_list *env_list, int *exit_code)
{
	char	*command;
	int		pipe_idx = 0;
	int		pipecnt;

	command = readline("minishell$ \033[s");
	if(command && *command) // 명령어 입력
	{
		add_history(command);
		t_block	*parsed_input = parsing(command, &pipecnt, env_list);
		if (parsed_input != NULL)
		{
			execute_command(pipecnt, parsed_input, env_list, exit_code);
			free_parsed_input(parsed_input, pipecnt);
		}
		free(command);
	}
	else if (!command) // ctrl-d 입력 -> 널포인터
	{
		printf("\033[u\033[1B\033[1Aexit\n");
		exit(0);
	}
	//else enter입력
	return(command);
}

int	main(int ac, char **av, char **env)
{
	t_env_list	*env_list;
	int			pipe_idx = 0;
	int			pipecnt;
	int			exit_code = 0;

	// atexit(check_leak);
	if (ac != 1)
		argc_err();
	set_signals();
	set_terminal();
	env_list = create_env_list();
	init_env_list(env, env_list);
	while(rl_gets(env_list, &exit_code));	
	free_env_list(env_list);
}
