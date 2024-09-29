/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/29 14:10:17 by hyoyoon          ###   ########.fr       */
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
static char	*rl_gets(t_blackhole *blackhole)
{
	char	*command;

	command = readline("minishell$ \033[s");
	if(command && *command) // 명령어 입력
	{
		add_history(command);
		parsing(command, blackhole);
		if (blackhole->exit_code == 0)
		{
			execute_command(blackhole);
			free_parsed_input(blackhole->parsed_input, blackhole->pipe_cnt);
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
	t_blackhole	*blackhole;
	int			pipe_idx = 0;
	int			pipecnt;
	int			exit_code = 0;

	// atexit(check_leak);
	if (ac != 1)
		argc_err();
	set_signals();
	set_terminal();
	blackhole = (t_blackhole *)malloc(sizeof(t_blackhole));
	if (blackhole == NULL)
		malloc_fail();
	blackhole->env_list = create_env_list();
	init_env_list(env, blackhole->env_list);
	blackhole->exit_code = 0;
	while(rl_gets(blackhole));	
	free_env_list(blackhole->env_list);
	free(blackhole);
}
