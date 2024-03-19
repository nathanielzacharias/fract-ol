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

#include "minilibx/mlx.h"

#include <fcntl.h>   // For open, close
#include <unistd.h>  // For read, write, close, perror, strerror, exit
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For perror, strerror

// void	*mlxptr;

// mlxptr = mlx_init();
// if(!mlxptr)
// 	return(1);

int main (void)
{

	int endian_test;
	int	local_endian;
	void	*mlxptr;

	endian_test = 0x11223344;
  	if (((unsigned char *)&endian_test)[0] == 0x11)
    	local_endian = 1;
  	else
    	local_endian = 0;


	mlxptr = mlx_init();
	if(!mlxptr)
		return(1);

	printf("mlxptr is: %p\n", mlxptr);
	printf("local endian is: %d", local_endian);



}