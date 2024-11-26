/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:37:42 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_token_arguments(char **tokens, t_command *cmd, int *j)
{
	int	i;

	i = 0;
	printf("enters in process token arguments\n");
	while (tokens[*j] && ft_strcmp(tokens[*j], "|"))
	{
		cmd->args[i] = ft_strdup(tokens[*j]);
		if (!cmd->args[i])
		{
			perror("Error duplicating token");
			exit(1);
		}
		i++;
		(*j)++;
	}
	cmd->args[i] = NULL;
}

int		expand_tokens(char **tokens, t_command *cmd, t_state *state)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	state->cmd = cmd;
	printf("------->enters expand_tokens<------\n");
	if (check_pair_quotes(cmd))
	{
		printf("Invalid quotes\n");
		return (1);    // <---------------- don't exit. free and error message
	}
	while (tokens[i])
	{
		
		if (ft_strchr(tokens[i], '$') || ft_strchr(tokens[i], '\"')
				|| ft_strchr(tokens[i], '\''))
		{
			if (ft_strchr(tokens[i], '\"') || ft_strchr(tokens[i], '\''))
			{
				printf("-->enters first condition of expand_quotes\n");
				process_quotes(cmd, state);
			}
			else
			{
				free(cmd->args[i]);
				printf("-->enters last condition of expand_quotes\n");
				cmd->args[i] = process_char_helper(tokens[i], &result, state);
			}
		}
		else
		{
			printf("enters the else block in expand_tokens\n");
			free(cmd->args[i]);
			cmd->args[i] = ft_strdup(tokens[i]);
		}
		printf("cmd->args[%d] in expand_tokens : %s\n", i, cmd->args[i]);
		printf("state->n[0] in expand_tokens : %d\n", state->n[0]);
		printf("tokens[%d] in expand_tokens : %s\n", i, tokens[i]);
		i++;
	}
	state->i = 0;
	return (0);
	for (int k = 0; cmd->args[k]; k++){printf("args[%d] end expand_tokens : %s\n", k, cmd->args[k]);} // <--- test
}

int		process_tokens(char **tokens, t_command *cmd, int *j)
{
	t_state	*state;
	int		i;

	i = 0;
	state = initialize_t_state();
	printf("------>enters process_tokens<-----\n");
	process_token_arguments(tokens, cmd, j);
	find_fd_in(cmd);
	find_fd_out(cmd);
	if (expand_tokens(tokens, cmd, state))
		return (1);
	free(state);
	return (0);
}

int		split_and_process_tokens(t_command *cmd, char **tokens, t_table *table)
{
	int	j;

	j = 0;
	while (tokens[j])
	{
		printf("enters while in split and process\n");
		if (process_tokens(tokens, cmd, &j))
			return (1);
		printf("after process tokens in split and process\n");
		if (tokens[j] && ft_strcmp(tokens[j], "|") == 0)
		{
			new_t_command(cmd, table);
			cmd = cmd->next;
			j++;
		}
	}
	return (0);
}

t_command	*tokenize_input(char *input, char **envp, int return_value)
{
	char		**tokens;
	t_table		*table;
	t_command	*cmd;
	t_command	*head;

	if (!input)
		return (NULL);
	table = initialize_t_main(input, envp, &return_value);
	cmd = initialize_t_command(table);
	if (!cmd)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	head = cmd;
	printf("input in tokenization : %s\n", input);
	tokens = ft_split(input, ' ');
	// for (int i = 0; tokens[i]; i++)                //<--------- test
	// {printf("tokens[%d] : %s\n", i, tokens[i]);}
	if (split_and_process_tokens(cmd, tokens, table))
	{
		free(cmd);
		return (NULL);
	}
	while (*tokens)
		free(*tokens++);
	return (head);
}
