/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:35:32 by nzachari          #+#    #+#             */
/*   Updated: 2024/03/18 23:35:44 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*exit gracefully*/
static void destroy_free_close(t_fractal *fractal, int err_flag)
{
	mlx_destroy_image(fractal->mlxptr, fractal->img.ptr);
	mlx_destroy_window(fractal->mlxptr, fractal->mlxwin);
	mlx_loop_end(fractal->mlxptr);
	mlx_destroy_display(fractal->mlxptr);
	free(fractal->mlxptr);
	if (!err_flag) 
		exit(0);
	else if (err_flag == 1)
		return (errno = EIO, perror(F_ERRGENERIC));
}

float map_win_to_complex(float ori_num, float min2, float max2, float max1)
{
	float new_dist;
	float ori_dist;
	float result;

	new_dist = max2 - min2;
	ori_dist = max1;
	result = ((ori_num) / ori_dist) * new_dist + min2;
	return	(result);
}

void	init_zoom(t_fractal *f)
{
	f->z.min_x = -2;
	f->z.max_x = 2;
	f->z.min_y = -2;
	f->z.max_y = 2;
	f->z.factor = 1;
	f->z.minxold = f->z.min_x;
	f->z.maxxold = f->z.max_x;
	f->z.minyold = f->z.min_y;
	f->z.maxyold = f->z.max_y;
}

/*init the values in struct with error handling*/
int run_initializers(t_fractal *fractal, char *name)
{
	fractal->divergence_threshold = 4;
	fractal->iter = ITERATIONS;
	fractal->name = name;

	fractal->mlxptr = mlx_init();
	if(!(fractal->mlxptr))
		return(destroy_free_close(fractal, 1), -1);
	fractal->mlxwin = mlx_new_window(fractal->mlxptr, WIDTH, HEIGHT, fractal->name);
	if(!(fractal->mlxwin))
		return (destroy_free_close(fractal, 1), -1);
	fractal->img.ptr = mlx_new_image(fractal->mlxptr, WIDTH, HEIGHT);
	if(!(fractal->img.ptr))
		return (destroy_free_close(fractal, 1), -1);
	fractal->img.pix_p = mlx_get_data_addr(fractal->img.ptr, &fractal->img.bpp, &fractal->img.line_l, &fractal->img.endian);
	init_zoom(fractal);
	return(0);
}


t_complex	sum_complex(t_complex *a, t_complex *b)
{
	t_complex result;

	result.re = a->re + b->re;
	result.im = a->im + b->im;
	return (result);
}

t_complex sq_complex(t_complex *z)
{
	t_complex result;

	result.re = pow(z->re, 2) - pow(z->im, 2);
	result.im = 2*(z->re)*(z->im);
	return (result);
}

void putpixel(int x, int y, t_img *img, int color)
{
	int offset;

	offset = (y * img->line_l) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pix_p + offset) = color;
}

float map_iter_to_argb(float i, int lower, int upper, int old_space)
{
	float color;
	int new_space;

	new_space = upper - lower;
	color = (i / old_space) * new_space + lower;

	// color %= 16;
	// char r;
	// char g;
	// char b;
	// b = ((color % (256)) + 7) >> 0;
	// g = ((color % (256)) + 17) >> 8;
	// r = ((color % (256)) + 27) >> 16;
	// color = (r | g | b);
	return	(color);
}

void	handle_pixel(int x, int y, t_fractal *f)
{
	t_complex	z;
	t_complex	c;
	t_complex	tmp;
	float i;
	float color;

	z.re = map_win_to_complex(x, f->z.min_x, f->z.max_x, WIDTH) ;
	z.im = map_win_to_complex(y, f->z.max_y, f->z.min_y, HEIGHT) ;
	c.re = f->z.min_x + x * (f->z.max_x - f->z.min_x) / WIDTH ;
	c.im = f->z.max_y + y * (f->z.min_y - f->z.max_y) / HEIGHT ;

	// check if point diverges
	i = -1;
	while (++i < f->iter)
	{
		tmp = sq_complex(&z);
		z = sum_complex(&tmp, &c);
		if ((pow(z.re, 2) + pow(z.im, 2)) > f->divergence_threshold)
		{
			color = map_iter_to_argb(i, PURPLE, WHITE, 2048);
			putpixel(x, y, &f->img, color);
			return ; 
		}
	}
	//else converges
	putpixel(x, y, &f->img, JAZZ_TURQUOISE);
}

/*threshold is -2 to +2, radius of 2*/
void	render(t_fractal *fractal)
{
	int x;
	int y;

	mlx_clear_window(fractal->mlxptr, fractal->mlxwin);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			handle_pixel(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlxptr, fractal->mlxwin, fractal->img.ptr, 0, 0);
}

int close_window(int k, t_fractal *f)
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

void	zoom(t_fractal *f, float k)
{
	// f->z.minxold = f->z.min_x;
	// f->z.maxxold = f->z.max_x;
	// f->z.minyold = f->z.min_y;
	// f->z.maxyold = f->z.max_y;

	f->z.max_x *= (1 + k);
	f->z.min_x *= (1 + k);
	f->z.max_y *= (1 + k);
	f->z.min_y *= (1 + k);
	f->z.factor = (1 + k);

}

int mouse_hook(int button, int x, int y, t_fractal *f)
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

void translate(int k, t_fractal *f)
{
	float dx;
	float dy;

	dx = f->z.max_x - f->z.min_x;
	dy = f->z.max_y - f->z.min_y;
	if (k == RG)
		{
			f->z.max_x += TRANSLATION_STEP * dx * f->z.factor;
			f->z.min_x += TRANSLATION_STEP * dx * f->z.factor;
		}
	else if (k == LF)
		{
			f->z.max_x -= TRANSLATION_STEP * dx * f->z.factor;
			f->z.min_x -= TRANSLATION_STEP * dx * f->z.factor;
		}
	else if (k == DW)
		{			
			f->z.max_y -= TRANSLATION_STEP * dy * f->z.factor;
			f->z.min_y -= TRANSLATION_STEP * dy * f->z.factor;
		}
	else if (k == UP)
		{
			f->z.max_y += TRANSLATION_STEP * dy * f->z.factor;
			f->z.min_y += TRANSLATION_STEP * dy * f->z.factor;
		}
}

int	key_hook(int k, t_fractal *f)
{
	if (k == UP || k == DW || k == LF || k == RG)
		translate(k, f);
	render(f);
	return (0);
}

int input_has_errors(int ac, char	*av[])
{
	(void) av;
	if(ac < 2 || ac > 4 || ac == 3)
		return(errno = EINVAL, perror(F_ERRARGS), 1);
	else
		return (0);
}

void choose_fractal(int ac, char *av[], t_fractal *f)
{
	
	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)))
		// do_mandelbrot(f, "mandelbrot");
		run_initializers(f, av[1]);
}

void listen_for_events(t_fractal *f)
{
	mlx_hook(f->mlxwin, 2, 1L<<0, close_window, f); //keypress ESC
	mlx_hook(f->mlxwin, 17, 0, clicked_close, f); //DestroyNotify
	mlx_mouse_hook(f->mlxwin, mouse_hook, f);
	mlx_key_hook(f->mlxwin, key_hook, f);
	mlx_loop(f->mlxptr);
}

int main (int ac, char *av[])
{
	t_fractal f;

	if (input_has_errors(ac, av))
		return (-42);
	else
	{
		choose_fractal(ac, av, &f);
		render(&f);
		listen_for_events(&f);
	}
	return (0);
}
	
	// int endian_test;
	// int	local_endian;
	// void	*mlxptr;

	// endian_test = 0x11223344;
 //  	if (((unsigned char *)&endian_test)[0] == 0x11)
 //    	local_endian = 1;
 //  	else
 //    	local_endian = 0;

// || (ac == 4 && !ft_strncmp(av[1], "julia", 5))