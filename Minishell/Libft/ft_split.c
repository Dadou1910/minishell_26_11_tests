/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abremont <abremont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:37:39 by jealefev          #+#    #+#             */
/*   Updated: 2024/11/22 07:03:30 by abremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *ft_strncpy(const char *src, size_t n)
{
    size_t  i;
    char    *dest;

    dest = malloc(sizeof(char) * (n + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (src[i] && i < n)
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
        dest[i++] = '\0';
    dest[i] = '\0';
    return (dest);
}


void	ft_free_split(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_countword(const char *str, char c)
{
	int	i;
	int	w;
	int	sq_counter;
	int	dq_counter;

	i = 0;
	w = 0;
	sq_counter = 0;
	dq_counter = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sq_counter = !sq_counter;
		else if (str[i] == '\"')
			dq_counter = !dq_counter;
		else if (str[i] != c && (i == 0 || str[i - 1] == c)
				&& !sq_counter && !dq_counter)
			w++;
		i++;
	}
	return (w);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;
	int		sq_counter;
	int		dq_counter;

	i = 0;
	k = 0;
	sq_counter = 0;
	dq_counter = 0;
	tab = malloc(sizeof(char *) * (ft_countword(s, c) + 3));
	if (!tab)
		return (0);
	while (s[i] && k <= ft_countword(s, c) + 1)
	{
		while (s[i] == c && !sq_counter && !dq_counter)
			i++;
		j = i;
		while (s[i])
		{
			if (s[i] == '\'' && !dq_counter)
				sq_counter = !sq_counter;
			else if (s[i] == '\"' && !sq_counter)
				dq_counter = !dq_counter;
			else if (s[i] == c && !sq_counter && !dq_counter)
				break;
			i++;
		}
		if (i > j)
		{
			tab[k] = ft_strncpy(s + j, i - j);
			if (!tab[k])
			{
				ft_free_split(tab, k);
				return (NULL);
			}
			k++;
		}
	}
	tab[k] = NULL;
	return (tab);
}


// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**tab;

// 	i = 0;
// 	k = 0;
// 	tab = malloc(sizeof(char *) * (ft_countword(s, c) + 1));
// 	if (!tab)
// 		return (0);
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		j = i;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (i > j)
// 		{
// 			tab[k] = ft_strncpy(s + j, i - j);
// 			k++;
// 		}
// 	}
// 	tab[k] = NULL;
// 	return (tab);
// }

// #include <stdio.h>
// int main(int argc, char **argv)
// {
//     if(argc == 3)
//         printf("%c \n",ft_split(argv[1], argv[2]));
//     return(0);}
