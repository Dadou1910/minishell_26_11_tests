/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:11:09 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/08 16:46:02 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		if (args[i + 1] != NULL)
			printf("%s ", args[i]);
		else
			printf("%s", args[i]);
		i++;
	}
}

void	echo_2(char **args)
{
	if (!args[2])
		return ;
	print_args(args, 2);
}

void	echo_1(char **args)
{
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	print_args(args, 1);
	printf("\n");
}

int	check_n_option(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_command *cmd)
{
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 2) == 0)
	{
		if (check_n_option(cmd->args[1]))
			echo_2(cmd->args);
		else
			echo_1(cmd->args);
	}
	else
		echo_1(cmd->args);
	return (0);
}
