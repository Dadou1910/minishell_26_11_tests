/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/20 08:12:10 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	deal_out_pipe(t_command *cmd)
{
	if (cmd->fd_out != -2)
	{
		close(cmd->p[READ_END]);
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_out);
	}
	else if (cmd->next != NULL)
	{
		close(cmd->p[READ_END]);
		if (dup2(cmd->p[WRITE_END], STDOUT_FILENO) == -1)
			perror("2dup2");
		// close(cmd->p[WRITE_END]);                       //<----------silenced this
	}
	close(cmd->p[WRITE_END]);
	// close(cmd->p[READ_END]);								//<----------silenced this
}

void	deal_in_pipe(t_command *cmd)
{
	if (cmd->fd_in != -2)
	{
		if (fcntl(cmd->fd_in, F_GETFD) == -1)
			perror("fd_in is not open or invalid");
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_in);
	}
	else if (cmd->pprev != -2)
	{
		if (fcntl(cmd->pprev, F_GETFD) == -1)
		{
			perror("pprev is not open or invalid");
		}
		if (dup2(cmd->pprev, STDIN_FILENO) == -1)
		{
			perror("dup2");
		}
		close(cmd->pprev);
	}
}
