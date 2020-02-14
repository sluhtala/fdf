/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:41:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/12 20:52:31 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord3d **scale_z(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].z = S_Z(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **scale_y(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].y = S_Y(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **scale_x(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].x = S_X(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **scale_xyz(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].x = S_X(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].y = S_Y(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].z = S_Z(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}
