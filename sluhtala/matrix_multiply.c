/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:50:41 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/18 19:23:25 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
t_vec3	matrix_multiply_4(t_vec3 r, double **m)
{
	t_vec3	result;

	printf("%.0f %.0f %.0f %.0f\n\n", r.x, r.y, r.z, r.w);

	printf("%.0f %.0f %.0f %.0f\n", m[0][0], m[0][1], m[0][2], m[0][3]);
	printf("%.0f %.0f %.0f %.0f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
	printf("%.0f %.0f %.0f %.0f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
	printf("%.0f %.0f %.0f %.0f\n", m[3][0], m[3][1], m[3][2], m[3][3]);
	printf("--------------------\n");
	//result.x = r.x * m[0][0] + r.y * m[1][0] + r.x * m[2][0] + r.w * m[3][0];
	//result.y = r.x * m[0][1] + r.y * m[1][1] + r.x * m[2][1] + r.w * m[3][1];
	//result.z = r.x * m[0][1] + r.y * m[1][2] + r.x * m[2][2] + r.w * m[3][2];
	//result.w = r.x * m[0][3] + r.y * m[1][3] + r.x * m[2][3] + r.w * m[3][3];
	
	result.x = r.x * m[0][0]+ r.y * m[0][1] + r.x * m[0][2] + r.w * m[0][3];
	result.y = r.x * m[1][0]+ r.y * m[1][1] + r.x * m[1][2] + r.w * m[1][3];
	result.z = r.x * m[1][0]+ r.y * m[2][1] + r.x * m[2][2] + r.w * m[2][3];
	result.w = r.x * m[3][0]+ r.y * m[3][1] + r.x * m[3][2] + r.w * m[3][3];
	return (result);
}
