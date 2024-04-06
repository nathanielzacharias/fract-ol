
//for every row in y
//	for every pix in x

void	handle_pixel(int x, int y, t_fractal *f)
{

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
			color = map_iter_to_argb(i, PURPLE, WHITE, COLORSPACE);
			putpixel(coord->x, coord->y, &f->img, color);
			return ;
		}
	}
	putpixel(coord->x, coord->y, &f->img, JAZZ_YELLOW);
}

float	map_win_to_complex(float ori_num, float min2, float max2, float max1)
{
	float	new_dist;
	float	ori_dist;
	float	res;

	new_dist = max2 - min2;
	ori_dist = max1;
	res = ((ori_num) / ori_dist) * new_dist + min2;
	return (res);
}