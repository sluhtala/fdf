/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:52:50 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/14 17:04:28 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord3d	**proj_ortho(t_coord3d **pnt, int lenx, int leny)
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
			pnt[y][i].x = P_OX(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z);
			pnt[y][i].y = P_OY(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z);
			pnt[y][i].z = P_OZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z);
			i++;
		}
		y++;
	}
	return (pnt);
}

t_coord3d	**proj_parallel(t_coord3d **pnt, int fov, int lenx, int leny)
{
	int i;
	int y;
static int n = 0;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			pnt[y][i].x = P_PAX(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z, fov, n);
			pnt[y][i].y = P_PAY(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z, fov, n);
			pnt[y][i].z = P_PAZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z, fov, n);
			i++;
		}
		y++;
	}
	n = n + 10;
	return (pnt);
}

t_coord3d	**proj_perspective(t_coord3d **pnt, int fov,int lenx, int leny)
{
	int i;
	int y;
	double z;
	double fa;
	double ne;
	double camera[3] = {50.0,50.0,0.0}; 	
	i = 0;
	y = 0;
	fa = 1000;
	ne = 0.01;
	while (y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			fa = pnt[y][i].z;
			pnt[y][i].x = P_PRX(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z, fov, fa, ne);
			pnt[y][i].y = P_PRY(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z, fov, fa, ne);
			pnt[y][i].z = P_PRZ(pnt[y][i].x, pnt[y][i].y, pnt[y][i].z, fov, fa, ne);
		//pnt[y][i].x = pnt[y][i].x * z;
		//pnt[y][i].y = pnt[y][i].y * z;
		//pnt[y][i].z = pnt[y][i].z * 0;		
			i++;
		}
		y++;
	}
	return (pnt);
}
