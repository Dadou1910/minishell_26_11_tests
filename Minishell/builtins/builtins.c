/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:11:17 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/20 09:08:53 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	deal_echo(t_command *cmd)
// {
// 	int	pid;

// 	pid = 0;
// 	if (pipe(cmd->p) == -1)
// 		perror("pipe");
// 	if (cmd->next != NULL)
// 		cmd->next->pprev = cmd->p[WRITE_END];
// 	pid = fork();
// 	if (pid == 0)
// 	{												//<---------- Changed original function deal_echo
// 		deal_in_pipe(cmd);
// 		deal_out_pipe(cmd);
// 		close(cmd->p[WRITE_END]);
// 		close(cmd->p[READ_END]);
// 		echo(cmd);
// 		exit(EXIT_SUCCESS);
// 	}
// 	wait(&pid);
// 	return (0);
// }

int	deal_echo(t_command *cmd)
{
	if (pipe(cmd->p) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (cmd->next != NULL)
		cmd->next->pprev = cmd->p[READ_END];
	cmd->table->pids[cmd->table->ipids] = fork();
	if (cmd->table->pids[cmd->table->ipids] == 0)
	{
		deal_in_pipe(cmd);
		deal_out_pipe(cmd);
		close(cmd->p[WRITE_END]);
		close(cmd->p[READ_END]);                      //<---------- Alternative function deal_echo?
		echo(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (cmd->table->pids[cmd->table->ipids] < 0)
	{
		perror("fork");
		return (-1);
	}
	cmd->table->ipids++;
	return (0);
}

int	deal_deal_echo(t_command *cmd)
{
	if (deal_echo(cmd) == -1)
		return (-1);
	if (cmd->pprev != -2)
		close(cmd->pprev);
	if (cmd->next == NULL)
	{
		if (cmd->p[READ_END] >= 0)
			close(cmd->p[READ_END]);
	}
	if (cmd->p[WRITE_END] >= 0)
		close(cmd->p[WRITE_END]);
	return (0);
}


int	is_builtins(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (deal_deal_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd->args));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env(cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset(&cmd->table->envp, cmd->args[1]));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		cmd->table->envp = ft_export(cmd->args[1], cmd->table->envp);
		return (1);
	}
	return (-1);
}
