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
	if (f->name == BURN)
	{
		f->z.min_x = -2.5;
		f->z.max_x = 1.5;
		f->z.min_y = 1.5;
		f->z.max_y = -2.5;
	}
	else
	{
		f->z.min_x = -2;
		f->z.max_x = 2;
		f->z.min_y = -2;
		f->z.max_y = 2;
	}
	f->z.factor = 1;
	f->color_lower = PURPLE;
	f->color_upper = WHITE;
	f->in_set_color = JAZZ_YELLOW;
}

void	zoom(t_fractal *f, int zoom_in)
{
	float	k;
	float	cx;
	float	cy;
	int		win_x_return;
	int		win_y_return;

	if (zoom_in)
		k = 1 - SCALING_STEP;
	else if (!zoom_in)
		k = 1 + SCALING_STEP;
	win_x_return = 1;
	win_y_return = 1;
	mlx_mouse_get_pos(f->mlxptr, f->mlxwin, &win_x_return, &win_y_return);
	cx = map_win_to_complex(win_x_return, f->z.min_x, f->z.max_x, WIDTH);
	cy = map_win_to_complex(HEIGHT - win_y_return, \
		f->z.min_y, f->z.max_y, HEIGHT);
	f->z.max_x = cx + (k * (f->z.max_x - cx));
	f->z.min_x = cx - (k * (cx - f->z.min_x));
	f->z.max_y = cy + (k * (f->z.max_y - cy));
	f->z.min_y = cy - (k * (cy - f->z.min_y));
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
