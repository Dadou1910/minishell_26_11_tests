/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:22:55 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// void	gestion_signaux;

char	*get_exit_code(int len, t_state *state)
{
	char	*env;

	// printf("--------->enters get_exit_code\n");
	env = ft_itoa(*(state->cmd->table->exit_code));
	if (env)
	{
		// state->n[0] += len;
		state->i += len;
	}
	// printf("state->i in get_exit_code $? : %d\n", state->i);
	// printf("state->n[0] in get_exit_code $? : %d\n", state->n[0]);
	return (env);
}

char	*dollar_question_case(char *arg, t_state *state)
{
	size_t	ij[2];
	size_t	total_size;
	char	*exit_c;

	ij[0] = 0;
	ij[1] = 0;
	total_size = 4096;
	printf("arg in dollar question case : %s\n", arg);
	exit_c = ft_itoa(*(state->cmd->table->exit_code));
	printf("exit_code in dollar question case : %s\n", exit_c);
	if (!exit_c)
		return (NULL);
	while (arg[ij[0]])
	{
		printf("ij[0] = %zu\n", ij[0]);
		if (arg[ij[0]] == '$' && arg[ij[0] + 1] == '?')
		{
			printf("calls concat_exit_code\n");
			concat_exit_code(exit_c, ij, total_size, state);
		}
		else
		{
			printf("enters else condition instead of concat exit code\n");
			state->env_var[ij[1]++] = arg[ij[0]++];
			// printf("env[j] = %c\n", env[ij[1]]);
		}
	}
	state->env_var[ij[1]] = '\0';
	printf("exit_env in dollar question case : %s\n", state->env_var);
	free(exit_c);
	return (state->env_var);
}

int	check_pair_quotes(t_command *cmd)
{
	int	i;
	int	j;
	int	count_sq;
	int	count_dq;

	i = 0;
	j = 0;
	count_dq = 0;
	count_sq = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '\'') || ft_strchr(cmd->args[i], '\"'))
		{
			while (cmd->args[i][j])
			{
				if (cmd->args[i][j] == '\'' && (count_dq % 2))
					count_sq++;
				if (cmd->args[i][j] == '\"' && (count_sq % 2))
					count_dq++;
				j++;
			}
		}
		i++;
	}
	if ((count_sq % 2) || (count_dq % 2))
		return (0);
	return (1);
}


