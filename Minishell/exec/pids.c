/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:25:24 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/08 17:48:53 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_pids(t_command *cmd)
{
	int	exit_code;
	int	status;
	int	i;

	exit_code = 0;
	status = 0;
	i = 0;
	while (i < cmd->table->num_pids)
	{
		if (cmd->table->pids[i] == -127)
			exit_code = -127;
		else
		{
			waitpid(cmd->table->pids[i], &status, 0);
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		i++;
	}
	return (exit_code);
}
