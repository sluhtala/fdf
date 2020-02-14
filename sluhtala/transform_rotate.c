/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:45:52 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/13 17:11:29 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord3d **rotate_z(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].x = R_ZX(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].y = R_ZY(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].z = R_ZZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **rotate_y(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].x = R_YX(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].y = R_YY(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].z = R_YZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d **rotate_x(t_coord3d **pnt, double num, int lenx, int leny)
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
			pnt[y][i].x = R_XX(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].y = R_XY(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			pnt[y][i].z = R_XZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z , num);
			i++;
		}
		y++;
	}
	return (pnt);
}
