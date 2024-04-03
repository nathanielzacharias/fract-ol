/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:14:00 by nzachari          #+#    #+#             */
/*   Updated: 2024/04/03 10:14:02 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

/*	Convert str to float. Depends on libft.
*/
float	ft_atof(char *str)
{
	char	*ori_ptr;
	double	result_atoi;
	double	result_post_decimal;
	size_t	len;
	int		sign;

	sign = 1;
	ori_ptr = str;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	result_atoi = (float) ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str && *str == '.')
		str++;
	result_post_decimal = (float) ft_atoi(str);
	len = ft_strlen(str);
	while (len--)
		result_post_decimal /= 10;
	return (sign * (result_atoi + result_post_decimal));
}

float	map_win_to_complex(float ori_num, float min2, float max2, float max1)
{
	float	new_dist;
	float	ori_dist;
	float	result;

	new_dist = max2 - min2;
	ori_dist = max1;
	result = ((ori_num) / ori_dist) * new_dist + min2;
	return (result);
}

float	map_iter_to_argb(float i, int lower, int upper, int old_space)
{
	float	color;
	int		new_space;

	new_space = upper - lower;
	color = (i / old_space) * new_space + lower;
	return (color);
}

t_complex	sum_complex(t_complex *a, t_complex *b)
{
	t_complex	result;

	result.re = a->re + b->re;
	result.im = a->im + b->im;
	return (result);
}

t_complex	sq_complex(t_complex *z)
{
	t_complex	result;

	result.re = pow(z->re, 2) - pow(z->im, 2);
	result.im = 2 * (z->re) * (z->im);
	return (result);
}
