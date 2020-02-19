/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:45:52 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/18 17:31:29 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//# define R_XX(x, y, z, a) 1 * x + 0 * y + 0 * z
//# define R_XY(x, y, z, a) 0 * x + y * cos(a) + z * -sin(a)
//# define R_XZ(x, y, z, a) 0 * x + y * sin(a) + z * cos(a)
//
//# define R_YX(x, y, z, a) cos(a) * x + 0 * y + sin(a) * z 
//# define R_YY(x, y, z, a) 0 * x + 1 * y + 0 * z
//# define R_YZ(x, y, z, a) -sin(a) * x + 0 * y + cos(a) * z
//
//# define R_ZX(x, y ,z, a) cos(a) * x + -sin(a) * y + 0 * z
//# define R_ZY(x, y ,z, a) sin(a) * x + cos(a) * y + 0 * z
//# define R_ZZ(x, y ,z, a) 0 * x + 0 * y + 1 * z

static double **make_xmatrix(double a)
{
	double	**tmat;

	tmat = (double**)malloc(sizeof(double*) * 4);
	tmat[0] = (double*)malloc(sizeof(double) * 4);
	tmat[1] = (double*)malloc(sizeof(double) * 4);
	tmat[2] = (double*)malloc(sizeof(double) * 4);
	tmat[3] = (double*)malloc(sizeof(double) * 4);
	tmat[0][0] = 1;
	tmat[0][1] = 0;
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = 0;
	tmat[1][1] = cos(a);
	tmat[1][2] = -sin(a);
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = sin(a);
	tmat[2][2] = cos(a);
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
	return(tmat);
}

//# define R_YX(x, y, z, a) cos(a) * x + 0 * y + sin(a) * z 
//# define R_YY(x, y, z, a) 0 * x + 1 * y + 0 * z
//# define R_YZ(x, y, z, a) -sin(a) * x + 0 * y + cos(a) * z

static double **make_ymatrix(double a)
{
	double	**tmat;

	tmat = (double**)malloc(sizeof(double*) * 4);
	tmat[0] = (double*)malloc(sizeof(double) * 4);
	tmat[1] = (double*)malloc(sizeof(double) * 4);
	tmat[2] = (double*)malloc(sizeof(double) * 4);
	tmat[3] = (double*)malloc(sizeof(double) * 4);
	tmat[0][0] = cos(a);
	tmat[0][1] = 0;
	tmat[0][2] = sin(a);
	tmat[0][3] = 0;
	tmat[1][0] = 0;
	tmat[1][1] = 1;
	tmat[1][2] = 0.0;
	tmat[1][3] = 0;
	tmat[2][0] = -sin(a);
	tmat[2][1] = 0.0;
	tmat[2][2] = cos(a);
	tmat[2][3] = 0;
	tmat[3][0] = 0;
	tmat[3][1] = 0;
	tmat[3][2] = 0;
	tmat[3][3] = 1.0;
	return(tmat);
}
static double **make_zmatrix(double a)
{
	double	**tmat;

	tmat = (double**)malloc(sizeof(double*) * 4);
	tmat[0] = (double*)malloc(sizeof(double) * 4);
	tmat[1] = (double*)malloc(sizeof(double) * 4);
	tmat[2] = (double*)malloc(sizeof(double) * 4);
	tmat[3] = (double*)malloc(sizeof(double) * 4);
	tmat[0][0] = cos(a);
	tmat[0][1] = -sin(a);
	tmat[0][2] = 0.0;
	tmat[0][3] = 0;
	tmat[1][0] = sin(a);
	tmat[1][1] = cos(a);
	tmat[1][2] = 0.0;
	tmat[1][3] = 0;
	tmat[2][0] = 0.0;
	tmat[2][1] = 0.0;
	tmat[2][2] = 1;
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

t_vec3 **transform_rotate_x(t_data data, double a)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_xmatrix(a);
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

t_vec3 **transform_rotate_y(t_data data, double a)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_ymatrix(a);
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

t_vec3 **transform_rotate_z(t_data data, double a)
{
	int		inx;
	int		ynx;
	double	**m;

	inx = 0;
	ynx = 0;
	m = make_zmatrix(a);
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

t_vec3 **rotate_z(t_vec3 **pnt, double num, int lenx, int leny)
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

t_vec3 **rotate_y(t_vec3 **pnt, double num, int lenx, int leny)
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

t_vec3 **rotate_x(t_vec3 **pnt, double num, int lenx, int leny)
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
