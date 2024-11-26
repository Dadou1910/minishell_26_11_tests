/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:05:14 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/11/12 12:37:27 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(t_command *cmd)
{
	char	**pathoche;
	char	*res;
	int		i;
	int		j;

	j = check_path_in_env(cmd->table->envp);
	if (j == -1)
		return (NULL);
	pathoche = ft_split(cmd->table->envp[j], ':');
	i = 0;
	while (pathoche[i])
	{
		res = check_access(pathoche, cmd->args[0], i);
		if (res)
			return (res);
		i++;
	}
	freetab(pathoche);
	return (NULL);
}

char	*path(char *cmd, char **envp)
{
	char	**total_path;
	char	*join_path;
	char	*path;
	int		i;

	i = check_path_in_env(envp);
	if (i == -1)
		return (NULL);
	total_path = ft_split(envp[i] + 5, ':');
	if (!total_path)
		perror("malloc");
	i = -1;
	while (total_path[++i])
	{
		join_path = ft_strjoin(total_path[i], "/");
		if (!join_path)
			(freetab(total_path), perror("malloc"));
		path = ft_strjoin(join_path, cmd);
		if (free(join_path), !path)
			(freetab(total_path), perror("malloc"));
		if (access(path, F_OK) == 0)
			return (freetab(total_path), path);
		free(path);
	}
	return (freetab(total_path), NULL);
}
