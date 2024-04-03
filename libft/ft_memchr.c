/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:47:07 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/30 18:47:55 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*s = "where is the love?";
	char	c = 'r';
	printf("result is: %p\n", ft_memchr(s, c, 7));
	printf("original is: %p\n", &s[3]);
}
*/
