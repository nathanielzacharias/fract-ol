/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:17:20 by nzachari          #+#    #+#             */
/*   Updated: 2024/04/03 10:17:22 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	zoom(t_fractal *f, float k)
{
	// f->z.max_x *= (1 + k);
	// f->z.min_x *= (1 + k);
	// f->z.max_y *= (1 + k);
	// f->z.min_y *= (1 + k);
	f->z.factor = (1 + k);

	float cx;
	cx = f->z.min_x;
	while (cx != f->z.max_x)
		cx++;
	cx /= 2;

	// cx = (f->z.max_x - f->z.min_x) / 2 + f->z.min_x;
	f->z.max_x = ((f->z.max_x - (cx)) * k) + cx;
	f->z.min_x = cx - (((cx) - f->z.min_x) * k);


	float cy;
	// cy = (f->z.max_y - f->z.min_y) / 2 + f->z.min_y;
	cy = f->z.min_y;
	while (cy != f->z.max_y)
		cy++;
	cy /= 2;

	f->z.max_y = ((f->z.max_y - (cy)) * k) + cy;
	f->z.min_y = cy - (((cy) - f->z.min_y) * k);
}

void	translate(int k, t_fractal *f)
{
	float	dx;
	float	dy;

	dx = f->z.max_x - f->z.min_x;
	dy = f->z.max_y - f->z.min_y;
	if (k == RG)
	{
		f->z.max_x += TSTEP * dx * f->z.factor;
		f->z.min_x += TSTEP * dx * f->z.factor;
	}
	else if (k == LF)
	{
		f->z.max_x -= TSTEP * dx * f->z.factor;
		f->z.min_x -= TSTEP * dx * f->z.factor;
	}
	else if (k == DW)
	{			
		f->z.max_y -= TSTEP * dy * f->z.factor;
		f->z.min_y -= TSTEP * dy * f->z.factor;
	}
	else if (k == UP)
	{
		f->z.max_y += TSTEP * dy * f->z.factor;
		f->z.min_y += TSTEP * dy * f->z.factor;
	}
}
