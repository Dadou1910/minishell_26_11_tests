/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_ressources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:18:06 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	allocate_resources(char **result, t_state **state)
{
	*result = malloc(sizeof(char) * 4096);
	if (!(*result))
	{
		perror("Error allocating memory for result");
		exit(1);
	}
	(*result)[0] = '\0';
	ft_bzero((*state)->n, sizeof(int) * 2);
	(*state)->i = 0;
	(*state)->sq_open = 0;
	(*state)->dq_open = 0;
}

char	*initialize_result(char *result, size_t result_size)
{
	if (!result)
	{
		result = malloc(result_size);
		if (!result)
		{
			perror("Memory allocation failed for result");
			exit(1);
		}
		result[0] = '\0';
	}
	return (result);
}

void	allocate_token_quotes(t_command *cmd, char *quotes[4096], t_state *state)
{
	cmd->token_quotes = malloc(sizeof(char *) * (state->n[1] + 1));
	if (!cmd->token_quotes)
	{
		perror("Error allocating memory for token_quotes");
		exit(1);
	}
	// printf("Before copy_quote_strings\n");
	copy_quote_strings(cmd, quotes, state);
}

char	*make_expand(const char *input, t_state *state)
{
	int		i;
	int		j;
	char	var_name[1024];
	char	*env_value;

	i = 1;
	j = 0;
	printf("input in make_expand : %s\n", input);
	printf("input[j] = %c\n", input[j]);
	while (input[j] == '$' && (input[i] == '\''
		|| input[i] == '\"'))
	{
		while (input[i++] == '\"')
			state->n[0]++;
		while (input[i++] == '\'')
			state->n[0]++;
		return (NULL);
	}
	if (input[i] == '?')
	{
		state->env_var = get_exit_code(1, state);
		state->i++;
		return (state->env_var);
	}
	if ((input[j] == '$' && !input[j + 1])
			|| (input[j] == '$' && input[j + 1] == '$'))
	{
		state->env_var = ft_strdup("$\0");
		state->i++;
		return (state->env_var);
	}
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		var_name[j] = input[i];
		printf("env_value[j] : %c\n", var_name[j]);
		i++;
		j++;
	}
	state->i += j;
	var_name[j] = '\0';
	
	if (i > 1)
	{
		env_value = getenv(var_name);
		state->i++;
		printf("enters the i > 0 condition\n");
		if (env_value)
		{
			state->env_var = ft_strdup(env_value);
			return (state->env_var);
		}
		else
			return (NULL);
	}
	printf("arrives at the end of function\n");
	while (input[i] && input[i] != '$')
	{
		printf("i : input[%d] : %c\n", i, input[i]);
		printf("j : input[%d] : %c\n", j, input[j]);
		printf("turns here\n");
		i++;
		j++;
	}
	state->i += j;
	state->env_var = ft_substr(input, j - 1, i - j);
	return (state->env_var);
}
