/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:15:58 by nzachari          #+#    #+#             */
/*   Updated: 2024/04/03 10:16:00 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	bit_shift_colors(t_fractal *f)
{
	f->color_lower = ((f->color_lower >> 8) | (f->color_lower << 17));
	f->color_upper = ((f->color_upper >> 17) | (f->color_upper << 8));
	f->in_set_color = ((f->in_set_color >> 8) | (f->in_set_color << 4));
}

int	key_hook(int k, t_fractal *f)
{
	if (k == UP || k == DW || k == LF || k == RG)
		translate(k, f);
	if (k == KEY_R)
		init_maxmin(f);
	if (k == KEY_SPACE)
		bit_shift_colors(f);
	render(f);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractal *f)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
		zoom(f, 1);
	else if (button == SCROLL_DOWN)
		zoom(f, 0);
	render(f);
	return (0);
}

int	close_window(int k, t_fractal *f)
{
	if (k == ESC)
		destroy_free_close(f, F_NO_ERR);
	return (0);
}

int	clicked_close(t_fractal *f)
{
	destroy_free_close(f, F_NO_ERR);
	return (0);
}
