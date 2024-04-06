/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzachari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:17:20 by nzachari          #+#    #+#             */
/*   Updated: 2024/04/03 10:17:22 by nzachari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	zoom(t_fractal *f, int zoom_in)
{
	float k;
	// (void) f;
	if (zoom_in)
	{
		// printf("zoom in is: %d\n", zoom_in );
		k = 1 - SCALING_STEP;
	}
	else if (!zoom_in)
		k = 1 + SCALING_STEP;
		// printf("zoom in is: %d\n", zoom_in );


	float dx;
		dx = ((f->z.max_x - f->z.min_x) / 2);
	float dy;
		dy = ((f->z.max_y - f->z.min_y) / 2);
	float cx;
		cx = f->z.min_x + dx;
	float cy;
		cy = f->z.min_y + dy;

	f->z.max_x = cx + (k * dx);
	f->z.min_x = cx - (k * dx);
	f->z.max_y = cy + (k * dy);
	f->z.min_y = cy - (k * dy);
}





// void	zoom(t_fractal *f, float k)
// {

// 	// f->z.max_x = k * f->z.max_x + (cx + dx) ;
// 	// f->z.min_x = k * f->z.min_x + (cx + dx) ;
	
// 	f->z.max_y = k * f->z.max_y + f->z.max_y ;
// 	f->z.min_y = k * f->z.min_y + f->z.min_y ;

// 	// float dx;
// 	// if (f->z.max_x >= 0)
// 	// 	dx = ((f->z.max_x - f->z.min_x) / 2);
// 	// else if (f->z.max_x < 0)
// 	// 	dx = (f->z.min_x - f->z.max_x) / 2;
// 	// float dy;
// 	// if (f->z.max_y >= 0)
// 	// 	dy = ((f->z.max_y - f->z.min_y) / 2);
// 	// else if (f->z.max_y < 0)
// 	// 	dx = (f->z.min_y - f->z.max_y) / 2;

// 	// if (cx >= 0)
// 	// 	f->z.max_x = k * (dx) + cx;
// 	// else if (cx < 0)
// 	// 	f->z.max_x = k * (dx) + cx;

// 	// if (cx >= 0)
// 	// 	f->z.min_x = -k * (dx) + cx;
// 	// else if (cx < 0)
// 	// 	f->z.min_x = -k * (dx) + cx;

	
// 	// float cy;
// 	// cy = f->z.min_y + dy;

// 	// if (cy >= 0)
// 	// 	f->z.max_y = k * (dy) + cy;
// 	// else if (cy < 0)
// 	// 	f->z.max_y = k * (dy) + cy;

// 	// if (cx >= 0)
// 	// 	f->z.min_y = -k * (dy) + cy;
// 	// else if (cx < 0)
// 	// 	f->z.min_y = -k * (dy) + cy;


// 	// printf("cx is: %f\n", cx );
// 	printf("max_x is: %f\n", f->z.max_x );
// 	printf("min_x is: %f\n", f->z.min_x );
// 	printf("dx is: %f\n", dx );


// 	// printf("cy is: %f\n", cy );
// 	printf("max_y is: %f\n", f->z.max_y );
// 	printf("min_y is: %f\n", f->z.min_y );
// 	printf("dy is: %f\n", dy );

// 	printf("\n");

// 	f->z.factor = (k + 1);
// }

void	translate(int k, t_fractal *f)
{
	float	dx;
	float	dy;

	dx = f->z.max_x - f->z.min_x;
	dy = f->z.max_y - f->z.min_y;
	if (k == RG)
	{
		f->z.max_x += TSTEP * dx * f->z.factor;
		f->z.min_x += TSTEP * dx * f->z.factor;
	}
	else if (k == LF)
	{
		f->z.max_x -= TSTEP * dx * f->z.factor;
		f->z.min_x -= TSTEP * dx * f->z.factor;
	}
	else if (k == DW)
	{			
		f->z.max_y -= TSTEP * dy * f->z.factor;
		f->z.min_y -= TSTEP * dy * f->z.factor;
	}
	else if (k == UP)
	{
		f->z.max_y += TSTEP * dy * f->z.factor;
		f->z.min_y += TSTEP * dy * f->z.factor;
	}
}
