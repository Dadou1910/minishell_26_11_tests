/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:32:53 by jeannelefev       #+#    #+#             */
/*   Updated: 2023/11/17 14:25:22 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

// #include "libft.h"
//
// int main(int argc, char **argv)
// {
// 	int integ;

// 	int arr[] = { 10, 2, 5, 0, 9, 3 };
// 	integ = ft_atoi(argv[1]);
// 	ft_bzero(arr, sizeof(int) * integ);
// 	for (int i = 0; i < 6; i++) {
// 		printf("%d\n", arr[i]);
// 	}
// 	return(0);
// }