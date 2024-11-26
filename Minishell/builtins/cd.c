/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:20:10 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/08 17:47:32 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char *line)
{
	if (access((const char *)line, F_OK | R_OK) != 0)
	{
		write(1, "cd: no such file or directory: '", 32);
		write(1, line, strlen(line));
		write(1, "'\n", 2);
		return ;
	}
	if (chdir((const char *)line) != 0)
	{
		perror("chdir() erreur");
		return ;
	}
}

void	ft_cd_wave(const char *path)
{
	const char	*home_directory;

	if (path == NULL || strlen(path) == 0)
	{
		ft_putendl_fd("Erreur : chemin invalide.\n", 2);
		return ;
	}
	if (strcmp(path, "~") == 0)
	{
		home_directory = getenv("HOME");
		if (home_directory == NULL)
			return ;
		if (chdir(home_directory) != 0)
			return ;
	}
}

int	cd(char **tab)
{
	char	*str;

	if (tab[1] == NULL)
		return (1);
	if (ft_strcmp(tab[1], "~") == 0)
	{
		ft_cd_wave(tab[1]);
	}
	else
	{
		str = ft_strjoin(tab[1], "/");
		ft_cd(str);
	}
	return (0);
}
