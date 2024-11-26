/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:24:02 by jealefev          #+#    #+#             */
/*   Updated: 2024/05/19 11:24:21 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*source;
	size_t	i;

	i = 0;
	source = (char *)src;
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (source[i] && i < dstsize - 1)
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	while (source[i])
		i++;
	return (i);
}

// #include <bsd/string.h>

// int main(void)
// {
// 	char src[] = "coucou";
// 	char dest[10]; memset(dest, 'A', 10);
// 	ft_strlcpy(dest, src, 1);
// 	printf("toi%s",dest);
// 	strlcpy(dest, src, 1);
// 	printf("lui%s",dest);

// 	return (0);
// }
