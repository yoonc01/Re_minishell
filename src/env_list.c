/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:47:13 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/20 16:45:09 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_env_add(char *env_key)
{
	if (env_key[0] >= '0' && env_key[0] <= '9')
		return (0);
	else
	{
		while (*env_key != 0)
		{
			if (!(ft_isalnum(*env_key) || *env_key=='_'))
				return (0);
			env_key++;
		}
	}
	return (1);
}

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

// 존재하는 환경변수 update하는 경우와 존재하지 않는 환경 변수를 새로 추가하는 경우에 대한 경우 처리 필요
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
}

int add_new_env_node(char *env, t_env_list *env_list)
{
	int		updated;
	char	**splited_env;
	char	*env_key;
	char	*env_value;

	splited_env = ft_split(env, '=');
	if (check_env_add(splited_env[0]) == 0)
		return (0);
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

//unset을 위한  함수
void	delete_env_node(char *str, t_env_list *env_list)
{
	t_env_node	*current_node;
	t_env_node	*temp;

	current_node = env_list->head;
	while (current_node->next != NULL)
	{
		if (my_strcmp(current_node->next->env_key, str) == 0)
		{
			temp = current_node->next;
			current_node->next = temp->next;
			free(temp->env_key);
			free(temp->env_value);
			free(temp);
		}
		current_node = current_node->next;
	}
}

void	free_env_list(t_env_list *env_list)
{
	t_env_node	*current_node;
	t_env_node	*temp;

	current_node = env_list->head;
	while(current_node != NULL)
	{
		free(current_node->env_key);
		free(current_node->env_value);
		temp = current_node;
		current_node = temp->next;
		free(temp);
	}
	free(env_list);
}