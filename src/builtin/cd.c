/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:05:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 12:57:04 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd_oldpwd(char *oldpwd,
				char *pwd, t_blackhole *blackhole);
static int	cd_dir(char *dir);
static int	cd_home(t_blackhole *blackhole);
static int	cd_fail(char *oldpwd);

int	ft_cd(t_blackhole *blackhole)
{
	t_inner_block	*current_node;
	char			*oldpwd;
	char			*pwd;

	current_node = blackhole->parsed_input->cmd_list->head->next;
	oldpwd = getcwd(NULL, 0);
	if (current_node != NULL)
	{
		if (cd_dir(current_node->str) == EXIT_FAILURE)
			return (cd_fail(oldpwd));
	}
	else
	{
		if (cd_home(blackhole) == EXIT_FAILURE)
			return (cd_fail(oldpwd));
	}
	pwd = getcwd(NULL, 0);
	ft_update_pwd_oldpwd(oldpwd, pwd, blackhole);
	free(oldpwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	cd_fail(char *oldpwd)
{
	free(oldpwd);
	return (EXIT_FAILURE);
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
	char	*addpwd;
	char	*addoldpwd;

	addpwd = ft_strjoin("PWD=", pwd);
	addoldpwd = ft_strjoin("OLDPWD=", oldpwd);
	add_env(addpwd, blackhole->env_list);
	add_env(addoldpwd, blackhole->env_list);
	free(addpwd);
	free(addoldpwd);
}
