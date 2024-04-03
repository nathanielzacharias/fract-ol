/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:55:33 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/11 13:32:37 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i] && little[j])
		{
			if (big[i + j] == little[j] && (i + j) < len)
				j++;
			else
				break ;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char *big = "where is the love?";
	char *little = "is";
	printf ("expect: %p, actual is: %p\n", &big[6], ft_strnstr(big, little,2));
	printf ("bsd is: %p\n", strnstr(big, little,2));
}
*/
