/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:25:41 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 08:12:12 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_single_quotes(char *arg, char *quotes[], t_state *state)
{
	char	*str;

	state->sq_open = !state->sq_open;
	if (state->sq_open)
	{
		str = helper_quotes(arg, '\'', state);
		if (str == NULL)
			return ;
		quotes[state->n[1]] = ft_strdup(str);
		if (str[0] != '\0' && str)
			state->n[1]++;
		// state->n[0]++;
		state->sq_open = 0;
		free(str);
	}
}

void	handle_double_quotes(char *arg, char **result, char *quotes[4096],
		t_state *state)
{
	char	*str;

	
	state->dq_open = !state->dq_open;
	if (state->dq_open)
	{
		str = helper_quotes(arg, '\"', state);
		if (str == NULL)
			return ;
		printf("str in dq_quote : %s\n", str);
		*result = process_char_helper(str, result, state);
		printf("result in handle dq start : %s\n", *result);
		if (*result && (*result)[0] != '\0')
		{
			printf("result before malloc double quotes : %s\n", *result);
			quotes[state->n[1]] = ft_strdup(*result);
			printf("quotes[%d] in if block : %s\n", state->n[1], quotes[state->n[1]]);
			state->n[1]++;
			state->n[0]++;
			printf("state->n[1] result : %d\n", state->n[1]);
			state->dq_open = 0;
			*result = NULL;
		}
		printf("quotes[%d] : %s\n", state->n[1], quotes[state->n[1]]);
		printf("result in handle dq end : %s\n", *result);
		free(str);
	}
}

void	handle_regular_char(char *arg, char *quotes[4096], t_state *state)
{
	quotes[state->n[1]] = malloc(2);
	if (!quotes[state->n[1]])
	{
		perror("Memory allocation failed");
		exit(1);
	}
	quotes[state->n[1]][0] = arg[state->n[0]];
	quotes[state->n[1]][1] = '\0';
	state->n[1]++;
	// state->n[0]++;
}

void	handle_dollar_sign(char *arg, char **result, char *quotes[],
		t_state *state)
{
	char	*str;

	// str = helper_quotes(arg, '\"', state);
	// if (str == NULL)
	// 	return ;
	str = make_expand(&arg[state->i], state);
	if (str)
		ft_strlcat(*result, str, 1024);
	if (*result && (*result)[0])
	{
		quotes[state->n[1]] = ft_strdup(*result);
		state->n[1]++;
		// state->n[0] += ft_strlen(str);
		*result = NULL;
	}
	free(str);
}
