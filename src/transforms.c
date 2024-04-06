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

void	init_maxmin(t_fractal *f)
{
	f->z.min_x = -2;
	f->z.max_x = 2;
	f->z.min_y = -2;
	f->z.max_y = 2;
	f->z.factor = 1;
}

void	zoom(t_fractal *f, int zoom_in)
{
	float	k;
	float	dx;
	float	dy;
	float	cx;
	float	cy;

	if (zoom_in)
		k = 1 - SCALING_STEP;
	else if (!zoom_in)
		k = 1 + SCALING_STEP;
	dx = ((f->z.max_x - f->z.min_x) / 2);
	dy = ((f->z.max_y - f->z.min_y) / 2);
	// cx = f->z.min_x + dx;
	// cy = f->z.min_y + dy;

	int	win_x_return;
	int	win_y_return;
	win_x_return = 1;
	win_y_return = 1;
	mlx_mouse_get_pos(f->mlxptr, f->mlxwin, &win_x_return, &win_y_return);
	if (win_x_return && win_y_return)
	{
		// cx = win_x_return;
		// cy = win_y_return;
		cx = map_win_to_complex(win_x_return, f->z.min_x, f->z.max_x, WIDTH);
		cy = map_win_to_complex(HEIGHT - win_y_return, f->z.min_y, f->z.max_y, HEIGHT);
	}
	else
	{
		cx = f->z.min_x + dx;
		cy = f->z.min_y + dy;
	}

	f->z.max_x = cx + (k * dx);
	f->z.min_x = cx - (k * dx);
	f->z.max_y = cy + (k * dy);
	f->z.min_y = cy - (k * dy);
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
