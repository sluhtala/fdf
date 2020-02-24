/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:23:43 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/24 16:31:47 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void draw_vertical(t_data *data, t_vec3 **point, int lenx, int leny)
{
	int i;
	int y;
	int p1[2];
	int p2[2];
	double col[2];

	y = 1;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			p1[0] = (int)point[y - 1][i].x + SCREENCENTER_X;
			p1[1] = (int)point[y - 1][i].y + SCREENCENTER_Y;
			p2[0] = (int)point[y][i].x + 	 SCREENCENTER_X;
			p2[1] = (int)point[y][i].y +     SCREENCENTER_Y;
			col[0] = (double)data->pnt[y - 1][i].color;
			col[1] = (double)data->pnt[y][i].color;
			draw_line(data, p1, p2, col);
			i++;
		}
		y++;
	}
}

static void draw_horizontal(t_data *data, t_vec3 **point, int lenx, int leny)
{
	int i;
	int y;
	int p1[2];
	int p2[2];
	double col[2];

	y = 0;
	while (y < leny)
	{
		i = 1;
		while (i < lenx)
		{
			p1[0] = (int)point[y][i - 1].x + SCREENCENTER_X;
			p1[1] = (int)point[y][i - 1].y + SCREENCENTER_Y;
			p2[0] = (int)point[y][i].x + SCREENCENTER_X;
			p2[1] = (int)point[y][i].y + SCREENCENTER_Y;
			col[0] = (double)data->pnt[y][i - 1].color;
			col[1] = (double)data->pnt[y][i].color;
			draw_line(data, p1, p2, col);
		i++;
		}
		y++;
	}
}

void	draw_grid(t_data *data)
{
	int lenx;
	int leny;
	t_vec3 **point;

	point = data->pnt;
	lenx = data->lenx;
	leny = data->leny;
	draw_horizontal(data, point, lenx, leny);
	draw_vertical(data, point, lenx, leny);
}
