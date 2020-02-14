/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:34:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/12 20:51:09 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord3d **move_z(t_coord3d **pnt, double num, int lenx, int leny)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			pnt[y][i].z = R_XZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **move_y(t_coord3d **pnt, double num, int lenx, int leny)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			pnt[y][i].y = T_Y(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **move_x(t_coord3d **pnt, double num, int lenx, int leny)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			pnt[y][i].x = T_X(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}
