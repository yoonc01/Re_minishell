/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:33:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/07 18:47:56 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	make_env_list(char **env)
{
	size_t	idx;
	char	*str;
	t_deque	*env_list;

	idx = 0;
	env_list = create_deque();
	while (env[idx] != NULL)
	{
		str = ft_strdup(env[idx]);
		insert_rear(env_list, str);
		idx++;
	}
	return (env_list);
}

int	main(int ac, char **av, char **env)
{
	ac;
	av;
	env;
	char *input = "hello I am Hyoyoon >> > < << <| | || 'sdf'   ";
	t_deque	*tokens = tokenize(input);
	while (tokens != NULL)
	{
		printf("%s\n", tokens->front->str);
		delete_front(tokens);
	}
}
