/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:38:11 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/12 18:57:28 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static int	abslt(int num)
{
	if (num < 0)
		return (-1 * num);
	else
		return (num);
}

static int initialize(int *dx, int *dy, int start[0], int end[2])
{
	int i;

	i = 1;
	if (*dx < 0)
	{
		i = -1;
		*dx = -*dx;
	}
	return (i);
}

void	draw_line_high(t_data *data, int start[2], int end[2], int col)
{
	int delta[2];
	int error;
	int point[2];
	int xi;

	delta[0] = end[0] - start[0];
	delta[1] = end[1] - start[1];
	xi = initialize(&delta[0], &delta[1], start, end);
	point[0] = start[0];
	point[1] = start[1];
	error = 2 * delta[0] - delta[1];
	while (point[1] < end[1])
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, point[0], point[1], col);
		if (error > 0)
		{
			point[0] = point[0] + xi;
			error = error - 2 * delta[1];
		}
		error = error + 2 * delta[0];
		point[1] = point[1] + 1;
	}
}

void	draw_line_low(t_data *data, int start[2], int end[2], int col)
{
	int delta[2];
	int error;
	int point[2];
	int yi;

	delta[0] = end[0] - start[0];
	delta[1] = end[1] - start[1];
	yi = initialize(&delta[1], &delta[0], start, end);
	point[0] = start[0];
	point[1] = start[1];
	error = 2 * delta[1] - delta[0];
	while (point[0] < end[0])
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, point[0], point[1], col);
		if (error > 0)
		{
			point[1] = point[1] + yi;
			error = error - 2 * delta[0];
		}
		error = error + 2 * delta[1];
		point[0] = point[0] + 1;
	}
}

void	draw_line(t_data *data, int start[2], int end[2], int col)
{
	if (abslt(end[1] - start[1]) < abslt(end[0] - start[0]))
	{
		if (start[0] > end[0])
			draw_line_low(data, end, start, col);
		else
			draw_line_low(data, start, end, col);
	}
	else
	{
		if (start[1] > end[1])
			draw_line_high(data, end, start, col);
		else
			draw_line_high(data, start, end, col);
	}
}
