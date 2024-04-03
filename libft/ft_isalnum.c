/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:35:58 by nzachari          #+#    #+#             */
/*   Updated: 2023/09/06 09:50:24 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
static int	ft_isalpha(unsigned char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

static int	ft_isnum(unsigned char c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_isalnum(unsigned char c)
{
	return (ft_isalpha(c) || ft_isnum(c));
}

/*
#include <stdio.h>
int	main(void)
{
	printf("f is: %i \n", ft_isalnum('f'));
	printf("4 is: %i \n", ft_isalnum('4'));
}
*/
