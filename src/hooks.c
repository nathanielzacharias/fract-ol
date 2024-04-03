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

int	key_hook(int k, t_fractal *f)
{
	if (k == UP || k == DW || k == LF || k == RG)
		translate(k, f);
	render(f);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractal *f)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
		zoom(f, SCALING_STEP);
	else if (button == SCROLL_DOWN)
		zoom(f, -1 * SCALING_STEP);
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
