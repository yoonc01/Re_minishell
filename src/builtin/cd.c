/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:05:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/05 12:23:43 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd_oldpwd(char *oldpwd,
				char *pwd, t_blackhole *blackhole);
static int	cd_dir(char *dir);
static int	cd_home(t_blackhole *blackhole);

int	ft_cd(t_blackhole *blackhole)
{
	t_inner_block	*current_node;
	char			*oldpwd;
	char			*pwd;

	current_node = blackhole->parsed_input->cmd_list->head->next;
	oldpwd = get_env("PWD", blackhole->env_list);
	if (current_node != NULL)
	{
		if (cd_dir(current_node->str) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (cd_home(blackhole) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL && errno == ENOENT)
		write(STDERR_FILENO,
			"cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n",
			108);
	ft_update_pwd_oldpwd(oldpwd, pwd, blackhole);
	return (EXIT_SUCCESS);
}

static int	cd_dir(char *dir)
{
	int	ret;

	ret = chdir(dir);
	if (ret < 0)
	{
		builtin_error2("cd: ", dir, ": No such file or directory");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	cd_home(t_blackhole *blackhole)
{
	char	*home_dir;
	int		ret;

	home_dir = get_env("HOME", blackhole->env_list);
	if (home_dir == NULL)
		return (EXIT_FAILURE);
	ret = chdir(home_dir);
	if (ret < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	ft_update_pwd_oldpwd(char *oldpwd,
				char *pwd, t_blackhole *blackhole)
{
	char			*temp;
	char			*addpwd;
	char			*addoldpwd;
	t_inner_block	*current_node;

	current_node = blackhole->parsed_input->cmd_list->head->next;
	if (pwd == NULL && errno == ENOENT)
	{
		temp = ft_strjoin(oldpwd, "/");
		pwd = ft_strjoin(temp, current_node->str);
		free(temp);
	}
	addpwd = ft_strjoin("PWD=", pwd);
	addoldpwd = ft_strjoin("OLDPWD=", oldpwd);
	add_env(addpwd, blackhole->env_list);
	add_env(addoldpwd, blackhole->env_list);
	free(addpwd);
	free(addoldpwd);
	free(pwd);
	free(oldpwd);
}
