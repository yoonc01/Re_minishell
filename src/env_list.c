/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:47:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 11:35:17 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*create_env_list(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (env_list == NULL)
		malloc_fail();
	env_list->head = NULL;
	env_list->size = 0;
	return (env_list);
}

int	update_env_node(t_env_list *env_list, char *env_key, char *env_value)
{
	t_env_node	*current_node;

	current_node = env_list->head;
	while (current_node != NULL)
	{
		if (my_strcmp(current_node->env_key, env_key) == 0)
		{
			free(current_node->env_value);
			free(current_node->env_key);
			current_node->env_key = env_key;
			current_node->env_value = env_value;
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

void	add_env_node(t_env_list *env_list, char *env_key, char *env_value)
{
	t_env_node	*new_node;
	t_env_node	*current_node;

	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	if (new_node == NULL)
		malloc_fail();
	new_node->env_key = env_key;
	new_node->env_value = env_value;
	new_node->next = NULL;
	if (env_list->head == NULL)
		env_list->head = new_node;
	else
	{
		current_node = env_list->head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	env_list->size = env_list->size + 1;
}

int	add_env(char *env, t_env_list *env_list)
{
	int		updated;
	char	**splited_env;
	char	*env_key;
	char	*env_value;

	splited_env = ft_split(env, '=');
	if (splited_env[0] == NULL)
		return (0);
	if (check_env_add(splited_env[0]) == 0)
	{
		split_free(splited_env);
		return (0);
	}
	env_key = ft_strdup(splited_env[0]);
	if (splited_env[1] == NULL)
		env_value = ft_strdup("");
	else
		env_value = ft_strdup(splited_env[1]);
	split_free(splited_env);
	updated = update_env_node(env_list, env_key, env_value);
	if (updated == 0)
		add_env_node(env_list, env_key, env_value);
	return (1);
}

void	free_env_list(t_env_list *env_list)
{
	t_env_node	*current_node;
	t_env_node	*temp;

	current_node = env_list->head;
	while (current_node != NULL)
	{
		free(current_node->env_key);
		free(current_node->env_value);
		temp = current_node;
		current_node = temp->next;
		free(temp);
	}
	free(env_list);
}
