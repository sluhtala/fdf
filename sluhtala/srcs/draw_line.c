/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:38:11 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 14:03:43 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

/*
** Takes in green and blue value (0 - 255)
** adds blue and green to max red
*/

static int tohex(int num)
{
	int color;
	int green;
	int blue;

	blue = num;
	green = num * 16 * 16;
	color = 0xff0000 + blue + green;
	return (color);
}

static int initialize(int *dx, int *dy, double *dcol, double col[2])
{
	int i;

	i = 1;
	if (*dx < 0)
	{
		i = -1;
		*dx = -*dx;
	}
	*dcol = (double)(col[1] - col[0]);
	return (i);
}

void	draw_line_high(t_data *data, int start[2], int end[2], double col[2])
{
	int delta[2];
	int error;
	int p[3];
	int xi;
	double dcol;

	delta[0] = end[0] - start[0];
	delta[1] = end[1] - start[1];
	p[2] = initialize(&delta[0], &delta[1], &dcol, col);
	if (delta[1] != 0)
		dcol = dcol / delta[1];
	p[0] = start[0];
	p[1] = start[1];
	error = 2 * delta[0] - delta[1];
	while (p[1] < end[1])
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, p[0], p[1], tohex(col[1]));
		if (error > 0)
		{
			p[0] = p[0] + p[2];
			error = error - 2 * delta[1];
		}
		col[1] = col[1] - dcol;
		error = error + 2 * delta[0];
		p[1] = p[1] + 1;
	}
}

/*
** Calculates the x and y distances
** Initializations checks if delta is negative and makes it to its opposite
** It also calculates the color difference
** Error is (deltay - 0.5 * deltax) but in int it (2 * deltay - deltax)  
** If the error is positive we move on the y axis else the y axis stay the same
*/

void	draw_line_low(t_data *data, int start[2], int  end[2], double col[2])
{
	int delta[2];
	int error;
	int p[3];
	double dcol;

	delta[0] = end[0] - start[0];
	delta[1] = end[1] - start[1];
	p[2] = initialize(&delta[1], &delta[0], &dcol, col);
	if (delta[1] != 0)
		dcol = dcol / delta[1];
	p[0] = start[0];
	p[1] = start[1];
	error = 2 * delta[1] - delta[0];
	while (p[0] < end[0])
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, p[0], p[1], tohex(col[1]));
		if (error > 0)
		{
			p[1] = p[1] + p[2];
			col[1] = col[1] - dcol;
			error = error - 2 * delta[0];
		}
		error = error + 2 * delta[1];
		p[0] = p[0] + 1;
	}
}

/*
** First check witch way the line is drawn comparing abs of x and y 
** Then check if the line is drawn backwards
** if it is: change color and change start to end
*/

void	draw_line(t_data *data, int start[2], int end[2], double col[2])
{
	double tcol[2];

	tcol[0] = col[1];
	tcol[1] = col[0];
	if (fabs((double)(end[1] - start[1])) < fabs((double)(end[0] - start[0])))
	{
		if (start[0] > end[0])
			draw_line_low(data, end, start, col);
		else
			draw_line_low(data, start, end, tcol);
	}
	else
	{
		if (start[1] > end[1])
			draw_line_high(data, end, start, col);
		else
			draw_line_high(data, start, end, tcol);	
	}
}
