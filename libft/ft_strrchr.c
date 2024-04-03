/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:40:03 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/08 16:50:51 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	const char *str = "Hello, World!";
    char target = 'o';

    char *result = ft_strrchr(str, target);

    if (result != NULL) 
    {
        printf("'%c' found at position: %ld\n", target, result - str);
    } 
    else 
    {
        printf("'%c' not found in the string.\n", target);
    }
    return 0;
}
*/