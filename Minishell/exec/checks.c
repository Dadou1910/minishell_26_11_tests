/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:04:36 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/11/12 12:32:54 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (-1);
}

void	bin_check(char *cmd)
{
	if (access(cmd, X_OK | F_OK) == 0)
		return ;
}

int	check_cmd(t_command *cmd, char **envp)
{
	char	*str;
	char	**command;

	if (ft_strcmp(cmd->args[0], "$?"))
		return (0);
	else if (ft_strncmp(cmd->args[0], "/bin/", 5) == 0)
		bin_check(cmd->args[0]);
	else
	{
		command = ft_split(cmd->args[0], ' ');
		if (command == NULL)
			perror("malloc");
		str = path(command[0], envp);
		if (str == NULL || cmd->args[0][0] == '.' || cmd->args[0][0] == '\0')
		{
			(free(str), freetab(command));
			command_not_found(cmd->args[0]);
			return (-1);
		}
		(free(str), freetab(command));
	}
	return (0);
}

char	*check_access(char **pathoche, char *cmd, int i)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(pathoche[i], "/");
	if (!tmp)
		return (freetab(pathoche), NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!res)
		return (freetab(pathoche), NULL);
	if (access(res, X_OK) == 0)
	{
		freetab(pathoche);
		return (res);
	}
	free(res);
	return (NULL);
}

int	check_path_in_env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (-1);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			return (i);
		i++;
	}
	return (-1);
}
