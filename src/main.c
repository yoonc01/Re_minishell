/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/05 14:56:03 by ycho2            ###   ########.fr       */
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

static int	rl_gets(t_blackhole *blackhole)
{
	char	*command;

	set_terminal(0);
	signal_default();
	command = readline("minishell$ ");
	if (command && *command)
	{
		add_history(command);
		parsing(command, blackhole);
		if (blackhole->exit_code == 0)
		{
			execute_command(blackhole);
			free_parsed_input(blackhole->parsed_input, blackhole->pipe_cnt);
		}
	}
	else if (!command)
	{
		printf("\033[1Bexit\n");
		exit(0);
	}
	free(command);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_blackhole	*blackhole;

	if (ac != 1 || av[1])
		argc_err();
	blackhole = (t_blackhole *)malloc(sizeof(t_blackhole));
	if (blackhole == NULL)
		malloc_fail();
	blackhole->env_list = create_env_list();
	init_env_list(env, blackhole->env_list);
	blackhole->exit_code = 0;
	while (rl_gets(blackhole))
		;
	free_env_list(blackhole->env_list);
	free(blackhole);
}
