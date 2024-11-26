/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:57:40 by jealefev          #+#    #+#             */
/*   Updated: 2024/05/19 11:22:46 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;
	long	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	return (nb * neg);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;

// 		printf("%d/",ft_atoi("   \n  \r  -42"));
// 		printf("%d",atoi("   \n  \r  -42"));
// 	return(0);
// }