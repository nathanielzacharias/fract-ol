/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:54:11 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/13 12:54:58 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	thislen(char const *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	len = thislen(s1) + thislen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char *)s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen((char *)s2))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "qwert";
	char *s2 = "hjkl";
	printf("%s\n", ft_strjoin(s1, s2));
}
*/