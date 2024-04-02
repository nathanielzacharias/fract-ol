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

#define WIDTH 800
#define HEIGHT 800
#define TRANSLATION_STEP 0.2
#define ITERATIONS 42


#define BLACK 0x0
#define WHITE 0xffffff
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define YELLOW 0xffff00
#define CYAN 0x00ffff
#define MAGENTA 0xff00ff
#define GRAY 0x808080
#define LIGHT_GRAY 0xc0c0c0
#define DARK_GRAY 0x404040
#define ORANGE 0xffa500
#define PURPLE 0x800080
#define PINK 0xffc0cb
#define BROWN 0xa52a2a
#define GOLD 0xffd700
#define SILVER 0xc0c0c0
#define JAZZ_BLUE 0x0073e6
#define JAZZ_GREEN 0x00cc66
#define JAZZ_PURPLE 0x9933ff
#define JAZZ_YELLOW 0xffd700
#define JAZZ_ORANGE 0xffa500
#define JAZZ_RED 0xcc3333
#define JAZZ_PINK 0xff66cc
#define JAZZ_CYAN 0x00ffff
#define JAZZ_TURQUOISE 0x40e0d0
#define JAZZ_MAGENTA 0xff00ff
#define JAZZ_LIME 0xbfff00
#define JAZZ_GOLD 0xffcc00
#define JAZZ_SILVER 0xc0c0c0
#define JAZZ_BRONZE 0xcd7f32
#define JAZZ_COPPER 0xb87333



/*Custom ERR messages to pass to perror()*/
#define F_ERRARGS "Usage: ./fractol \"mandelbrot\" or ./fractol \"julia\" <num> <num>"
#define F_ERRMALLOC "malloc() returned NULL, could not alloc memory"
#define F_ERRMLXPTR "creating ptr for MLX ptr/display/window/img returned null"
#define F_ERRGENERIC "Exited with err_flag == 1"

/*keys*/
#define UP 65362
#define DW 65364
#define LF 65361
#define RG 65363
#define ESC 65307

typedef struct s_img
{
	void	*ptr;
	char	*pix_p;
	int		bpp;
	int		endian;
	int		line_l;
} t_img;

typedef struct s_zoom
{
	double min_x;
	double max_x;
	double min_y;
	double max_y;
} t_zoom;

typedef struct s_fractal
{
	char	*name;
	void	*mlxptr;
	void	*mlxwin;
	t_img	img;
	double	divergence_threshold;
	ssize_t	iter;
	t_zoom	z;

} t_fractal;


typedef struct s_complex
{
	double	re;
	double	im;
} t_complex;


#endif