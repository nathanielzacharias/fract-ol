/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:57:37 by nzachari          #+#    #+#             */
/*   Updated: 2024/03/23 19:57:39 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H


#include "../minilibx-linux/mlx.h"

#include <fcntl.h>   // For open, close
#include <unistd.h>  // For read, write, close, perror, strerror, exit
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For perror, strerror

#include <math.h>
#include <errno.h>


#include "../libft/libft.h"

#define WIDTH 1600
#define HEIGHT 1600

/*Custom ERR messages to pass to perror()*/
#define F_ERRARGS "Usage: ./fractol \"mandelbrot\" or ./fractol \"julia\" <num> <num>"
#define F_ERRMALLOC "malloc() returned NULL, could not alloc memory"

typedef struct s_img
{
	void	*img_p;
	char	*pix_p;
	int		bpp;
	int		endian;
	int		line_l;
} t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlxptr;
	void	*mlxwin;
	t_img	img;

} t_fractal;


typedef struct s_complex
{
	double	re;
	double	im;
} t_complex;

#endif