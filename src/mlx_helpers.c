/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:08:28 by nzachari          #+#    #+#             */
/*   Updated: 2024/04/03 10:08:31 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	putpixel(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_l) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pix_p + offset) = color;
}

/*	Init the values in struct with error handling
*/
int	run_initializers(t_fractal *fractal, int name, char *title)
{
	fractal->divergence_threshold = DIVERGENCE_THRESHOLD;
	fractal->iter = ITERATIONS;
	fractal->name = name;
	fractal->mlxptr = mlx_init();
	if (!(fractal->mlxptr))
		return (destroy_free_close(fractal, 1), -1);
	fractal->mlxwin = mlx_new_window(fractal->mlxptr, WIDTH, HEIGHT, title);
	if (!(fractal->mlxwin))
		return (destroy_free_close(fractal, 1), -1);
	fractal->img.ptr = mlx_new_image(fractal->mlxptr, WIDTH, HEIGHT);
	if (!(fractal->img.ptr))
		return (destroy_free_close(fractal, 1), -1);
	fractal->img.pix_p = mlx_get_data_addr(fractal->img.ptr, &fractal->img.bpp, \
		&fractal->img.line_l, &fractal->img.endian);
	init_maxmin(fractal);
	return (0);
}

/*	This is a helper func for handle_pixel. Needed to split for Norm.
*/
static void	putcolor(t_complex *z, t_complex *c, t_coord *coord, t_fractal *f)
{
	float		i;
	float		color;
	t_complex	tmp;

	i = -1;
	while (++i < f->iter)
	{
		tmp = sq_complex(z);
		*z = sum_complex(&tmp, c);
		if (pow(z->re, 2) + pow(z->im, 2) > f->divergence_threshold)
		{
			color = map_iter_to_argb(i, f->color_lower, f->color_upper, CDIV);
			putpixel(coord->x, coord->y, &f->img, color);
			return ;
		}
	}
	putpixel(coord->x, coord->y, &f->img, f->in_set_color);
}

void	handle_pixel(int x, int y, t_fractal *f)
{
	t_complex	z;
	t_complex	c;
	t_coord		coord;

	z.re = map_win_to_complex(x, f->z.min_x, f->z.max_x, WIDTH);
	z.im = map_win_to_complex(y, f->z.max_y, f->z.min_y, HEIGHT);
	if (f->name == MANDELBROT)
	{
		c.re = x * (f->z.max_x - f->z.min_x) / WIDTH + f->z.min_x;
		c.im = y * (f->z.min_y - f->z.max_y) / HEIGHT + f->z.max_y;
	}
	else if (f->name == JULIA)
	{
		c.re = f->julia_c_re;
		c.im = f->julia_c_im;
	}
	coord.x = x;
	coord.y = y;
	putcolor(&z, &c, &coord, f);
	return ;
}

/*	Exit gracefully
*/
void	destroy_free_close(t_fractal *fractal, int err_flag)
{
	mlx_loop_end(fractal->mlxptr);
	mlx_destroy_image(fractal->mlxptr, fractal->img.ptr);
	mlx_destroy_window(fractal->mlxptr, fractal->mlxwin);
	mlx_destroy_display(fractal->mlxptr);
	free(fractal->mlxptr);
	if (!err_flag)
		exit(0);
	else if (err_flag == 1)
		return (errno = EIO, perror(F_ERRGENERIC));
}
