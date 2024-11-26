/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:19:04 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_state_quotes(t_state *state)
{
	state->i = 0;
	state->sq_open = 0;
	state->dq_open = 0;
}

void	update_quotes(char ch, t_state *state, char *result, size_t result_size)
{
	if (ch == '\'' && !state->dq_open)
	{
		state->sq_open = !state->sq_open;
		ft_strlcat(result, "\'", result_size);
	}
	else if (ch == '\"' && !state->sq_open)
	{
		state->dq_open = !state->dq_open;
		ft_strlcat(result, "\"", result_size);
	}
}

char	*process_char_helper(const char *input, char **result, t_state *state)
{
	size_t	result_size;
	char	temp[2];
	int		handle;
	char	*env;

	result_size = 4096;
	handle = -1;
	env = NULL;
	*result = initialize_result(*result, result_size);
	printf("result start of process_char : %s\n", *result);
	printf("state->i : %d\n", state->i);
	printf("input[state->i] : %c\n", input[state->i]);
	while (input[state->i])
	{
		if (!state->env_var)
			state->env_var = malloc(4096);
		temp[0] = input[state->i];
		temp[1] = '\0';
		printf("temp[0] : %c\n", temp[0]);
		update_quotes(input[state->i], state, *result, result_size);
		printf("input in process char helper : %s\n", input);
		// printf("input[%d]: %c\n", state->i, input[state->i]);
		if (input[state->i] == '$' && !state->sq_open)
		{
			printf("enters $ condition in process_char_helper\n");
			env = make_expand(&input[state->i], state);
			printf("state->env_var in process_char_helper : %s\n", state->env_var);
			if (env)
				ft_strlcat(*result, env, result_size);
			free(env);
			printf("state->i : %d\n", state->i);
		}
		else if (input[state->i++])
			ft_strlcat(*result, temp, result_size);
		else
			state->i++;
	}
	handle_state_quotes(state);
	return (*result);
}

char	*process_char(char *input, char *result, t_state *state, t_command *cmd)
{
	allocate_resources(&result, &state);
	state->cmd = cmd;
	handle_quotes_and_expand(input, result, cmd, state);
	return (result);
}

void	handle_quotes_and_expand(char *arg, char *result, t_command *cmd,
		t_state *state)
{
	char	*quotes[4096];

	state->n[0] = 0;
	ft_bzero(quotes, sizeof(char *) * 4096);
	printf("innput in handle_quotes_qnd_expand : %s\n", arg);
	printf("state->n[0] start of handle_quotes_and_expand : %d\n", state->n[0]);
	while (arg[state->n[0]])
	{
		printf("state->n[0] start handle_quotes_and_expand : %d\n", state->n[0]);
		printf("arg[state->n[0]] start handle_quotes_and_expand : %c\n", arg[state->n[0]]);
		if (arg[state->n[0]] == '\'')
		{
			printf("--->enters sq in handle_quotes\n");
			handle_single_quotes(arg, quotes, state);
		}
		else if (arg[state->n[0]] == '\"')
		{
			printf("--->enters dq in handle_quotes\n");
			handle_double_quotes(arg, &result, quotes, state);
		}
		else if (arg[state->n[0]] == '$' && !state->sq_open)
		{
			printf("--->enters $ in handle_quotes\n");
			handle_dollar_sign(&arg[state->n[0]], &result, quotes, state);
		}
		else
		{
			printf("--->enters regular char in handle_quotes\n");
			handle_regular_char(arg, quotes, state);
		}
		if (state->n[1] >= 4096)
		{
			perror("Too many quoted strings");
			exit(1);
		}
		printf("state->n[0] end handle_quotes_and_expand : %d\n", state->n[0]);
		printf("arg[state->n[0]] in handle_quotes_and_expand : %c\n", arg[state->n[0]]);
	}
	printf("result end of handle_quotes_and_expand : %s\n", result);
	quotes[state->n[1]] = NULL;
	printf("state->n[1] end of expand_tokens : %d\n", state->n[1]);
	allocate_token_quotes(cmd, quotes, state);
}
