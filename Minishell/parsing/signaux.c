/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:39:45 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/26 06:58:29 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_sig = 0;

void sig_int(int signum)
{
	int	checker;

	checker = 0;
	if (g_sig == 200)
		checker = 1;
    (void)signum;
    g_sig = 130;
    ft_putstr_fd("\n", STDERR);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (!checker)
		rl_redisplay();
}

void sig_quit(int signum)
{
    (void)signum;
    if (g_sig == 200)
    {
        ft_putstr_fd("Quit: core dumped\n", STDERR);
        g_sig = 131;
    }
    else
    {
        ft_putstr_fd("\b\b  \b\b", STDERR);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

char *read_input(char **env)
{
	char *line = get_line(env);
	if (!line)
		rl_clear_history();
	return (line);
}

void handle_signal_interrupts(char *line)
{
	if (g_sig == 130 || g_sig == 131)
	{
		g_sig = 0;
		free(line);
	}
	else if (g_sig == 200)
	{
		g_sig = 131;
	}
}

void	concat_exit_code(char *exit_c, size_t *ij, size_t total_size, t_state *state)
{
	if (state->env_var)
	{
		printf("env in concat exit code start : %s\n", state->env_var);
		ft_strlcat(state->env_var, exit_c, total_size);
		printf("enters strlcat in concat_exit_code\n");
	}
	else
	{
		state->env_var = exit_c;
		printf("enters elsem in concat_exit_code\n");
	}
	printf("env in concat exit code : %s\n", state->env_var);
	ij[1] += ft_strlen(exit_c);
	ij[0] += 2;
}