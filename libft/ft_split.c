/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:30:41 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/16 21:31:29 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countw(char const *s, char c)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			is_word = 0;
		}
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	w_length(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static int	fr_res(char **res, int i)
{
	while (i > 0)
		free (res[--i]);
	free (res);
	return (1);
}

static int	write_word(char const *s, char c, char **res, int wc)
{
	size_t	len;
	int		j;
	int		i;

	i = -1;
	while (++i < (int)wc)
	{
		while (*s == c)
			s++;
		len = w_length(s, c);
		res[i] = malloc((len + 1) * sizeof(char));
		if (!res[i] && fr_res(res, i))
			return (0);
		j = -1;
		while (++j < (int)len)
			res[i][j] = *s++;
		res[i][len] = '\0';
	}
	res[wc] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		wc;
	int		check;

	wc = countw(s, c);
	res = (char **)malloc((wc + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	check = write_word(s, c, res, wc);
	if (check == 0)
		return (NULL);
	return (res);
}
