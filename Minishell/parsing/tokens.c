/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:19:23 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*helper_quotes(char *arg, char c, t_state *state)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = state->n[0];
	state->i = 0;
	printf("state->n[0] in str maker start : %d\n", state->n[0]);
	if (arg[j] != '$')
		j++;
	str = malloc(1024);
	while ((arg[j] != c && arg[j]))
	{
		// printf("dq_open : %d\n", state->dq_open);
		// printf("sq_open : %d\n", state->sq_open);
		str[i++] = arg[j++];
		if ((!state->dq_open && !state->sq_open && arg[j] == '\'')
			|| (!state->sq_open && !state->dq_open && arg[j] == '\"'))
			{
				break ;
				printf("j in str maker : %d\n", j);
			}
	}
	str[i] = '\0';
	if (!str)
	{
		if (state->dq_open || state->sq_open)
			state->n[0]++;
	}
	else if (!ft_strchr(str, '$') || state->sq_open || (ft_strchr(arg, '$')
			&& state->dq_open) || (ft_strchr(arg, '$') && !state->dq_open))
		{
			state->n[0] = j + 1;
			printf("enters long condition in str maker\n");
		}
	printf("str : %s\n", str);
	printf("state->n[0] in str maker end : %d\n", state->n[0]);
	return (str);
}

void	copy_quote_strings(t_command *cmd, char *quotes[4096], t_state *state)
{
	int	i;

	i = 0;
	for (int k = 0; quotes && quotes[k]; k++)             //<--------------test
		printf("quotes[%d] : %s\n", k, quotes[k]);
	while (quotes && quotes[i])
	{
		printf("quotes[%d] : %s\n", i, quotes[i]);
		cmd->token_quotes[i] = ft_strdup(quotes[i]);
		printf("cmd->token_quotes[%d] : %s\n", i, cmd->token_quotes[i]);
		i++;
	}
	cmd->token_quotes[i] = NULL;
	for (int x = 0; cmd->token_quotes[x]; x++)                   //<------------test
	{printf("token_quotes[%d] end of copy strings : %s\n", x, cmd->token_quotes[x]);}
	i = 0;
	while (quotes[i])
		free(quotes[i++]);
	cmd->token_quotes[state->n[1]] = NULL;
}

char	*copy_quotes_to_arg(t_command *cmd, int *i)
{
	int	total_size;
	int	j;

	j = 0;
	total_size = 0;
	if (cmd->token_quotes){for (int k = 0; cmd->token_quotes[k]; k++) // <-------------- test
		printf("token_quotes[%d] start copy_quote_to_arg : %s\n", k, cmd->token_quotes[k]);}
	while (cmd->token_quotes && cmd->token_quotes[j])
		total_size += strlen(cmd->token_quotes[j++]);
	free(cmd->args[(*i)]);
	cmd->args[(*i)] = malloc(total_size + 1);
	if (!cmd->args[(*i)])
	{
		perror("Error allocating memory for concatenated args");
		exit(1);
	}
	cmd->args[(*i)][0] = '\0';
	j = 0;
	while (cmd->token_quotes && cmd->token_quotes[j])
	{
		ft_strlcat(cmd->args[(*i)], cmd->token_quotes[j], total_size + 1);
		free(cmd->token_quotes[j]);
		j++;
	}
	free(cmd->token_quotes);
	// int x = 0;                                              // <------------------------test
	// while (cmd->args && cmd->args[x])
	// {
	// 	printf("args[%d] : %s\n", x, cmd->args[x]);
	// 	x++;
	// }
	return (cmd->args[*i]);
}

void	process_quotes(t_command *cmd, t_state *state)
{
	int	i;

	i = 0;
	printf("enters process_quotes\n");
	while (cmd->args[i])
	{
		printf("right before check_pair_quotes in process_quotes\n");
		// if (ft_strchr(cmd->args[i], '$') && ft_strchr(cmd->args[i], '?'))
		// {
		// 	printf("args[i] : %s\n", cmd->args[i]);
		// 	cmd->args[i] = dollar_question_case(cmd->args[i], state);
		// }
		if (ft_strchr(cmd->args[i], '\'') || ft_strchr(cmd->args[i], '\"')
			|| (ft_strchr(cmd->args[i], '$')
			&& !ft_strncmp(cmd->args[0], "$?", 2)))
		{
			printf("args[i] in process_quotes : %s\n", cmd->args[i]);
			cmd->args[i] = process_char(cmd->args[i], cmd->args[i], state, cmd);
			cmd->args[i] = copy_quotes_to_arg(cmd, &i);
			printf("i in process_quotes : %d\n", i);
		}
		i++;
	}
}

void	allocate_args(t_command *cmd)
{
	cmd->args = malloc(sizeof(char *) * 1024);
	if (!cmd->args)
	{
		perror("Error allocating memory for args");
		exit(1);
	}
}
