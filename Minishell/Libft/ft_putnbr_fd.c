/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:37:27 by jealefev          #+#    #+#             */
/*   Updated: 2024/05/19 11:23:47 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	a;

	if (nb == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	if (nb < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-nb, fd);
	}
	if (nb > 9)
	{
		a = nb % 10 - '0';
		write(fd, &a, 1);
		ft_putnbr_fd(nb / 10, fd);
	}
	if (nb < 10 && nb > 0)
	{
		a = nb - '0';
		write(fd, &a, 1);
	}
}
