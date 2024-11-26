/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/12 12:41:03 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_pipe(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

int	open_fct_check(char *file, int i)
{
	int	filein;

	filein = 0;
	if (i == 0)
		filein = open(file, O_RDONLY);
	else if (i == 1)
		filein = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		filein = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (filein);
}

void	free_t_command(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd->next;
		freetab(cmd->args);
		free(cmd->table->pids);
		free(cmd);
		cmd = temp;
	}
}

void	new_t_command(t_command *cmd, t_table *table)
{
	t_command	*new_cmd;

	new_cmd = initialize_t_command(table);
	cmd->next = new_cmd;
}
