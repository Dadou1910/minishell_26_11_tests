/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:55 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/08 18:01:02 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->table || !cmd->table->envp || !cmd->table->envp[0])
		return (-42);
	while (cmd->table->envp[i] && cmd->table->envp[i][0] != '\0')
	{
		printf("%s\n", cmd->table->envp[i]);
		i++;
	}
	return (0);
}
