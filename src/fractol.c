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

// void	*mlxptr;

// mlxptr = mlx_init();
// if(!mlxptr)
// 	return(1);

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

void run_initializers(t_fractal *fractal)
{
	fractal->mlxptr = mlx_init();
	if(!(fractal->mlxptr))
		return(errno = ENOMEM, perror(F_ERRMALLOC));
}


int main (int ac, char *av[])
{

	if(ac < 2 || ac > 4 || ac == 3)
		return(errno = EINVAL, perror(F_ERRARGS), 1);
	
	// int endian_test;
	// int	local_endian;
	// void	*mlxptr;

	// endian_test = 0x11223344;
 //  	if (((unsigned char *)&endian_test)[0] == 0x11)
 //    	local_endian = 1;
 //  	else
 //    	local_endian = 0;

	// mlxptr = mlx_init();
	// if(!mlxptr)
	// 	return(1);

	// void	*win;
	// win = mlx_new_window(mlxptr, 500, 500, "Title1");
	// if(!win)
	// 	return(1);

	// void *img;
	// img = mlx_new_image(mlxptr, 500, 500);

	// char *imgdata;
	// int 	bpp;
	// int 	sl;
	// int 	endian;
	// imgdata = mlx_get_data_addr(img, &bpp, &sl, &endian);

 //  	// mlx_clear_window(mlxptr,win);


	// // sleep(2);

	// printf("mlxptr is: %p\n", mlxptr);
	// printf("local endian is: %d\n", local_endian);
	// printf("imgdata is: %p", imgdata);

	// mlx_loop(mlxptr);

	// mlx_destroy_window(mlxptr, win);


	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10) ) || (ac == 4 && !ft_strncmp(av[1], "julia", 5)))
	{
		printf("to be continued \n");
		// run_initializers();
	}	
	return (0);
}