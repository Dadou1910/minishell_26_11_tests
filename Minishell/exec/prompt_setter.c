/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:46:58 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/11/15 10:03:13 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_line_to_history(const char *line)
{
	if (line && *line)
	{
		add_history(line);
	}
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char	*tmp;

	tmp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		tmp = ft_strjoin(cwd, " >> ");
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

char	**get_env(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (envp[i] != NULL)
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*get_line(char **envp)
{
	int		i;
	char	*line;
	char	*prompt;

	i = 0;
	prompt = get_prompt();
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line || ft_strcmp(line, "exit") == 0)
	{
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free(envp);
		return (NULL);
	}
	return (line);
}
