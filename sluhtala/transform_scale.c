/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:41:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/18 19:30:57 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double **make_smatrix(double x, double y, double z)
{
	double	**tmat;

	tmat = (double**)malloc(sizeof(double*) * 4);
	tmat[0] = (double*)malloc(sizeof(double) * 4);
	tmat[1] = (double*)malloc(sizeof(double) * 4);
	tmat[2] = (double*)malloc(sizeof(double) * 4);
	tmat[3] = (double*)malloc(sizeof(double) * 4);
	tmat[0][0] = x;
	tmat[0][1] = 0.0;
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = 0.0;
	tmat[1][1] = y;
	tmat[1][2] = 0.0;
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = 0.0;
	tmat[2][2] = z;
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
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
t_vec3 **scale_z(t_vec3 **pnt, double num, int lenx, int leny)
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

t_vec3 **scale_y(t_vec3 **pnt, double num, int lenx, int leny)
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

t_vec3 **scale_x(t_vec3 **pnt, double num, int lenx, int leny)
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

t_vec3 **scale_xyz(t_vec3 **pnt, double num, int lenx, int leny)
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

t_vec3 **transform_scale(t_data data, double x, double y, double z)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_smatrix(x, y, z);
	while (ynx < data.leny)
	{
		inx = 0;
		while (inx < data.lenx)
		{
			data.pnt[ynx][inx] = matrix_multiply_4(data.pnt[ynx][inx], m);
			inx++;
		}
		ynx++;
	}
	free_matrix(&m);
	return (data.pnt);
}
