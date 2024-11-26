/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:39:45 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 06:59:53 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_table	*initialize_t_main(char *line, char **envp, int *return_value)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	table->num_pids = ft_count_pipe(line);
	table->pids = malloc(sizeof(int) * table->num_pids + 1);
	i = 0;
	while (i < table->num_pids)
	{
		table->pids[i] = -1;
		i++;
	}
	table->ipids = 0;
	table->envp = envp;
	table->exit_code = return_value;
	return (table);
}

t_command	*initialize_t_command(t_table *table)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	cmd->args = malloc(sizeof(char *) * 4096);
	if (!cmd->args)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	cmd->fd_in = -2;
	cmd->here_doc = -2;
	cmd->lim = NULL;
	cmd->fd_out = -2;
	cmd->pprev = -2;
	cmd->table = table;
	cmd->next = NULL;
	cmd->token_quotes = NULL;
	return (cmd);
}

t_state	*initialize_t_state(void)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	ft_bzero(state->n, sizeof(int) * 2);
	state->i = 0;
	state->dq_open = 0;
	state->sq_open = 0;
	state->cmd = NULL;
	state->env_var = malloc(4096);
	return (state);
}
