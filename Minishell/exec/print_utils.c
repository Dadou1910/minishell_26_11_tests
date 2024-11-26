/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeannelefevre <jeannelefevre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:05:30 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/10/30 21:19:41 by jeannelefev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_not_found(char *cmd)
{
	write(1, "Command not found: ", 19);
	write(1, cmd, ft_strlen(cmd));
	write(1, "\n", 1);
}

void	print_command(t_command *cmd)
{
	int	i;

	i = 0;
	printf("Arguments: ");
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			printf("%s ", cmd->args[i]);
			i++;
		}
	}
	printf("\n");
	printf("fd_in: %d\n", cmd->fd_in);
	printf("fd_out: %d\n", cmd->fd_out);
	printf("Pipe read_end: %d, write_end: %d\n", cmd->p[0], cmd->p[1]);
	printf("Previous pipe input (pprev): %d\n", cmd->pprev);
	if (cmd->next)
		printf("Next command exists.\n");
	else
		printf("No next command.\n");
}
