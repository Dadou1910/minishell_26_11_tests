/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealefev <jealefev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:17:46 by jealefev          #+#    #+#             */
/*   Updated: 2024/05/19 11:24:53 by jealefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	a;

	i = 0;
	j = 0;
	a = 0;
	while (s1[i])
	{
		if (s1[i] == *set)
			a++;
		i++;
	}
	tab = malloc(sizeof(char) * ft_strlen(s1) - a + 1);
	while (s1[i])
	{
		if (s1[i] != *set)
			tab[j] = s1[i];
		i++;
	}
	return (tab);
}
