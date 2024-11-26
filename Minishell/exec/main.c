/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:03:20 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 09:13:00 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	launch_exec(t_command *cmd, char **envp)
{
	execute_cmd(cmd, envp);
	// printf("pprev in launch_exec : %d\n", cmd->pprev);
	if (cmd->pprev != -2)
		close(cmd->pprev);
	if (cmd->next == NULL && cmd->p[READ_END] >= 0)
		close(cmd->p[READ_END]);
	if (cmd->p[WRITE_END] >= 0)
		close(cmd->p[WRITE_END]);
}

int	flunch(t_command *cmd, char **envp)
{
	int			val;
	int			return_value;
	t_command	*quentin;

	quentin = cmd;
	while (cmd && cmd->args[0])
	{
		val = is_builtins(cmd);
		if (val == -1 && check_cmd(cmd, envp) == 0)
		{
			g_sig = 200;
			launch_exec(cmd, envp);
		}
		else
		{
			cmd->table->pids[cmd->table->ipids] = val;    //<-------- Invalid read
			cmd->table->ipids++;
		}
		cmd = cmd->next;
	}
	return_value = wait_pids(quentin);
	if (g_sig == 130 || g_sig == 131)
		return_value = g_sig;
	g_sig = 0;
	return (return_value);
}

char	**exec_command(char *line, char **envp, int *return_value)
{
	char		**env;
	t_command	*cmd;

	if (check_line(line) == -1)
		return (envp);
	add_line_to_history(line);
	cmd = fill_t_command(line, envp, *return_value);
	if (!cmd)
		return (NULL);
	*return_value = flunch(cmd, envp);
	env = cmd->table->envp;
	if (cmd)
	{
		if (cmd->table)
			free(cmd->table->pids);
		free_cmd(cmd);
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		return_value;
	char	**env;

	return_value = 0;
	env = get_env(envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		signal(SIGINT, &sig_int);
		signal(SIGQUIT, &sig_quit);
		if (!env)
			env = get_env(envp);
		line = read_input(env);
		if (!line)
			break;
		if (line[0] != '\0' && line[0] != '\n')
			env = exec_command(line, env, &return_value);
		if (g_sig == 130 || g_sig == 131 || g_sig == 200)
		{
			handle_signal_interrupts(line);
			continue;
		}
		free(line);
	}
	return (0);
}
