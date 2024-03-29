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

// void	compute_fractal()
// {
// 	t_complex	z;
// 	t_complex	c;
// 	ssize_t iter;
// 	double temp_real;

// 	z.re = 0;
// 	z.im = 0;
// 	c.re = 0.25;
// 	c.im = 0.4;

// 	iter = -1;
// 	while (++iter < 30)
// 	{
// 		// z.re = pow(z.re, 2) - pow(z.im, 2);
// 		// z.re = (z.re * z.re) - (z.im * z.im);
// 		temp_real = pow(z.re, 2) - pow(z.im, 2);
// 		z.im = 2 * z.re * z.im;
// 		z.re = temp_rea0.2l;
// 		z.re += c.re;
// 		z.im += c.im;
// 		// printf("iter is: %d, z.re is: %f, z.im is: %f \n", iter, z.re, z.im);
// 	}
// }

/*exit gracefully*/
static void destroy_free_close(t_fractal *fractal)
{
	printf("in destroy free close \n");
	mlx_destroy_window(fractal->mlxptr, fractal->mlxwin);
	mlx_destroy_display(fractal->mlxptr);
	free(fractal->mlxptr);
	errno = ENOMEM;
	perror(F_ERRMLXPTR);
}

/*init the values in struct with error handling*/
int run_initializers(t_fractal *fractal, char *name)
{
	fractal->divergence_threshold = 4;
	fractal->iter = 210;
	fractal->name = name;

	fractal->mlxptr = mlx_init();
	if(!(fractal->mlxptr))
		return(destroy_free_close(fractal), -1);

	fractal->mlxwin = mlx_new_window(fractal->mlxptr, WIDTH, HEIGHT, fractal->name);
	if(!(fractal->mlxwin))
		return (destroy_free_close(fractal), -1);

	fractal->img.ptr = mlx_new_image(fractal->mlxptr, WIDTH, HEIGHT);
	if(!(fractal->img.ptr))
		return (destroy_free_close(fractal), -1);

	fractal->img.pix_p = mlx_get_data_addr(fractal->img.ptr, &fractal->img.bpp, &fractal->img.line_l, &fractal->img.endian);


	return(0);
	//events_init(fractal);
	//data_init(fractal);
}

double map(double ori_num, double min2, double max2, double max1)
{
	double new_dist;
	double ori_dist;
	double result;

	new_dist = max2 - min2;
	ori_dist = max1;
	result = ((ori_num) / ori_dist) * new_dist + min2;
	return	(result);
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

void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	t_complex	tmp;
	double i;
	double color;

	z.re = map(x, -2, 2, WIDTH);
	z.im = map(y, 2, -2, HEIGHT);

	c.re = z.re;
	c.im = z.im;
	// c.re = 0.285;
	// c.im = 0.01;

	// check if point diverges
	i = -1;
	while (++i < fractal->iter)
	{
		tmp = sq_complex(&z);
		z = sum_complex(&tmp, &c);
		// printf("z.re is: %f\n", z.re );

		//if hypotenuse > 2, diverges
		if ((pow(z.re, 2) + pow(z.im, 2)) > fractal->divergence_threshold)
		{
			// color = map(i/60, CYAN, MAGENTA, fractal->iter);
			color = map(i/5, PURPLE, WHITE, 2701*65);
			putpixel(x, y, &fractal->img, color);
			return ; 
		}
	}
	//else converges
	putpixel(x, y, &fractal->img, JAZZ_TURQUOISE);
}

/*threshold is -2 to +2, radius of 2*/
void	render(t_fractal *fractal)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlxptr, fractal->mlxwin, fractal->img.ptr, 0, 0);
}

int main (int ac, char *av[])
{
	t_fractal fractal;

	if(ac < 2 || ac > 4 || ac == 3)
		return(errno = EINVAL, perror(F_ERRARGS), -1);


	else if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10) ) )
	{
		int check;		
		check = run_initializers(&fractal, av[1]);
		if (check == -1)
			return(-1);
		printf("run_init returns: %d\n", check);

		render(&fractal);

		mlx_loop(fractal.mlxptr);
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