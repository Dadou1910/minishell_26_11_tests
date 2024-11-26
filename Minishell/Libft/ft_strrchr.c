/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:33:49 by jeannelefev       #+#    #+#             */
/*   Updated: 2024/05/19 11:24:42 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char    *ft_strrchr(const char *s, int a)
// {
// 	int	i;

// 	i = ft_strlen(s) - 1;
// 	while (s[i] && i >= 0)
// 	{
// 		if (s[i] == a )
// 			return ((char *)&s[i]);
// 		i--;
// 	}
// 	return (NULL);
// }

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	c = (char)c;
	i = ft_strlen(s) - 1;
	if (c == 0)
		return ((char *)&s[strlen(s)]);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// int main(void)
// {
// 	char *c;
// 	c = ft_strrchr("tripouille", 0);
// 	printf("%s \n",c);
// }
