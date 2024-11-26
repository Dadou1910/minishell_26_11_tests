/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:19 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/20 08:15:23 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_command *cmd, char **envp)
{
	char	*pathoche;

	if (!cmd || !cmd->args || !cmd->args[0])
		perror("invalid command");
	if (ft_strncmp(cmd->args[0], "/", 1) == 0)
		pathoche = cmd->args[0];
	else
		pathoche = find_path(cmd);
	if (!pathoche)
	{
		perror("command not found");
		free(cmd->table->pids);
		free(cmd->table);
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(pathoche, cmd->args, envp) == -1)
	{
		free(pathoche);
		perror("command execution failed");
	}
}

int	execute_cmd(t_command *cmd, char **envp)
{
	if (pipe(cmd->p) == -1)
		perror("pipe");
	if (cmd->next != NULL)
		cmd->next->pprev = cmd->p[READ_END];
	cmd->table->pids[cmd->table->ipids] = fork();
	if (cmd->table->pids[cmd->table->ipids] == 0)
	{
		if (cmd->here_doc != -2)
			cmd->fd_in = here_doc(cmd->lim);
		deal_in_pipe(cmd);
		deal_out_pipe(cmd);
		close(cmd->p[WRITE_END]);
		close(cmd->p[READ_END]);
		execute(cmd, envp);
		perror("execute");
		exit(EXIT_FAILURE);
	}
	else if (cmd->table->pids[cmd->table->ipids] < 0)
		perror("fork");
	else
		close(cmd->p[WRITE_END]);
	cmd->table->ipids++;
	return (0);
}
