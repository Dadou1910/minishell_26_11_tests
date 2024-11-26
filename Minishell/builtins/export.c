/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:03:09 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/12 12:33:47 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_export(char *exported, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (exported[len] && exported[len] != '=')
		len++;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(exported, envp[i], len) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**export_1(char *exported, char **envp, int al_here)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (get_env_size(envp) + 1));
	while (envp[i])
	{
		if (i == al_here)
			res[i] = ft_strdup(exported);
		else
			res[i] = ft_strdup(envp[i]);
		i++;
	}
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (res);
}

char	**export_2(char *exported, char **envp)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (get_env_size(envp) + 2));
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		i++;
	}
	res[i] = ft_strdup(exported);
	return (res);
}

char	**ft_export(char *exported, char **envp)
{
	char	**res;
	int		al_here;

	al_here = check_export(exported, envp);
	if (al_here != 0)
		res = export_1(exported, envp, al_here);
	else
		res = export_2(exported, envp);
	return (res);
}
