/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:52:50 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/20 15:36:28 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//# define P_PRX(x, y, z, f, fa, ne) x * (1 / (tan(f / 2 * (M_PI / 180)))) + 0 * y + 0 * z + 1 * 0
//# define P_PRY(x, y, z, f, fa, ne) x * 0 + y * (1 / (tan(f / 2 * (M_PI / 180)))) + 0 * z + 1 * 0
//# define P_PRZ(x, y, z, f, fa, ne) x * 0 + y * 0 + z * -(fa/ (fa - ne)) -1
static double **make_persmatrix(double s, double l, double r, double near, double far, t_data data)
{
	double	**tmat;

	tmat = (double**)malloc(sizeof(double*) * 4);
	tmat[0] = (double*)malloc(sizeof(double) * 4);
	tmat[1] = (double*)malloc(sizeof(double) * 4);
	tmat[2] = (double*)malloc(sizeof(double) * 4);
	tmat[3] = (double*)malloc(sizeof(double) * 4);
	tmat[0][0] = s * 1 / (data.width / data.length);
	tmat[0][1] = 2 * near / (r -l);
	tmat[0][2] = 0.0;
	tmat[0][3] = (r + l) / (r - l);
	tmat[1][0] = 0.0;
	tmat[1][1] = 0;
	tmat[1][2] = 2 * near / (s - -(s));
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = 0.0;
	tmat[2][2] = -(far + near) / (far - near);
	tmat[2][3] = -2 * (far * near) / (far - near);
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = -1;
	tmat[3][3] = 0;
	return(tmat);
}

static void	free_matrix(double ***m)
{
	int i;

	if (!*m)
		return ;
	i = 0;
	while (i < 4)
	{
		free((*m)[i]);
		i++;
	}
	free(*m);
}

t_vec3 **transform_perspective(t_data data, double fov)
{
	int		inx;
	int		ynx;
	double	near;
	double	far;
	double	**m;
	double l;
	double r;

	near = 0.1;
	far = 100;
	r = (data.width / data.length) * (tan(fov * 0.5 * M_PI / 180) * near);
	l = -r;
	fov = (tan((fov / 2) *  (M_PI / 180)) * near);
	inx = 0;
	ynx = 0;
	m = make_persmatrix(fov,l, r, near, far, data);
	while (ynx < data.leny)
	{
		inx = 0;
		while (inx < data.lenx)
		{
			data.pnt[ynx][inx] = matrix_multiply_4(data.pnt[ynx][inx], m);
			if (data.pnt[ynx][inx].w != 1 && data.pnt[ynx][inx].w != 0)
			{
				data.pnt[ynx][inx].x /= data.pnt[ynx][inx].w;
				data.pnt[ynx][inx].y /= data.pnt[ynx][inx].w;
				data.pnt[ynx][inx].z /= data.pnt[ynx][inx].w;	
			}	
			inx++;
		}
		ynx++;
	}
	free_matrix(&m);
	return (data.pnt);
}


t_vec3	**proj_ortho(t_vec3 **pnt, int lenx, int leny)
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

t_vec3	**proj_parallel(t_vec3 **pnt, int fov, int lenx, int leny)
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

t_vec3	**proj_perspective(t_vec3 **pnt, int fov,int lenx, int leny)
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
