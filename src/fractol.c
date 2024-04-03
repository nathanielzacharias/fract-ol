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

#include <fractol.h>

/*	Threshold is -2 to +2, radius of 2
*/
void	render(t_fractal *fractal)
{
	int	x;
	int	y;

	mlx_clear_window(fractal->mlxptr, fractal->mlxwin);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			handle_pixel(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlxptr, fractal->mlxwin, \
		fractal->img.ptr, 0, 0);
}

/*	Checks for ac.
*	If Julia, checks that params are between -2 and 2.
*/
int	input_has_errors(int ac, char	*av[])
{
	float	test1;
	float	test2;

	if (ac < 2 || ac > 4 || ac == 3)
		return (errno = EINVAL, perror(F_ERRARGS), 1);
	else if (ac == 4)
	{
		test1 = ft_atof(av[2]);
		test2 = ft_atof(av[3]);
		if (test1 >= 2 || test1 <= -2 || test2 >= 2 || test2 <= -2)
			return (errno = EINVAL, perror(F_ERRJULIA), 1);
	}
	return (0);
}

/*	Second case is default for Julia when no params passed
*/
int	choose_fractal_error(int ac, char *av[], t_fractal *f)
{
	size_t i;

	i = 0;
	while (i < 1 + ft_strlen(av[1]))
	{
		av[1][i] = ft_tolower(av[1][i]);
		i++;
	}
	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)))
		return (run_initializers(f, MANDELBROT, av[1]));
	else if ((ac == 2 && !ft_strncmp(av[1], "julia", 5)))
	{
		f->julia_c_re = ft_atof("0.355");
		f->julia_c_im = ft_atof("0.355");
		return (run_initializers(f, JULIA, av[1]));
	}
	else if ((ac == 4 && !ft_strncmp(av[1], "julia", 5)))
	{
		f->julia_c_re = ft_atof(av[2]);
		f->julia_c_im = ft_atof(av[3]);
		return (run_initializers(f, JULIA, av[1]));
	}
	return (1);
}

void	listen_for_events(t_fractal *f)
{
	mlx_hook(f->mlxwin, KEYPRESS, 1L << 0, close_window, f);
	mlx_hook(f->mlxwin, DESTROY_NOTIFY, 0, clicked_close, f);
	mlx_mouse_hook(f->mlxwin, mouse_hook, f);
	mlx_key_hook(f->mlxwin, key_hook, f);
	mlx_loop(f->mlxptr);
}

int	main(int ac, char *av[])
{
	t_fractal	f;

	if (input_has_errors(ac, av))
		return (errno);
	else
	{
		if(choose_fractal_error(ac, av, &f))
			return(errno = EINVAL, perror(F_ERRARGS), 1);
		render(&f);
		listen_for_events(&f);
	}
	return (0);
}
