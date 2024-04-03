/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:21:24 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/14 22:21:28 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s1_in_set(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		else
			s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (start <= end && s1_in_set(set, s1[start]))
		start++;
	while (end > start && s1_in_set(set, s1[end]))
		end--;
	newstr = malloc((end - start + 2) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_bzero(newstr, end - start + 2);
	ft_strlcpy(newstr, &s1[start], end - start + 2);
	return (newstr);
}

/*
#include <stdio.h>
int	main(void)
{
	char *s1 = "aaabbaa";
	char *set = "a";
	printf("%s\n", ft_strtrim(s1, set));
}
*/
