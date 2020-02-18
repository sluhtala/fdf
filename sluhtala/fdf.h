/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:32:04 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/18 19:29:31 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define esc_key 53 
# define up_key 126
# define down_key 125
# define left_key 123
# define right_key 124
# define space_key 49
# define num_key(num) 17 + num



# define T_X(x, y, z, vx) 1 * x + 0 * y + 0 * x + 1 * vx
# define T_Y(x, y, z, vy) 0 * x + 1 * y + 0 * z + 1 * vy
# define T_Z(x, y, z, vz) 0 * x + 0 * y + 1 * z + 1 * vz

# define S_X(x, y, z, s) s * x + 0 * y + 0 * z + 0 * 1
# define S_Y(x, y, z, s) 0 * x + s * y + 0 * z + 0 * 1
# define S_Z(x, y, z, s) 0 * x + 0 * y + s * z + 0 * 1

# define R_XX(x, y, z, a) 1 * x + 0 * y + 0 * z
# define R_XY(x, y, z, a) 0 * x + y * cos(a) + z * -sin(a)
# define R_XZ(x, y, z, a) 0 * x + y * sin(a) + z * cos(a)

# define R_YX(x, y, z, a) cos(a) * x + 0 * y + sin(a) * z 
# define R_YY(x, y, z, a) 0 * x + 1 * y + 0 * z
# define R_YZ(x, y, z, a) -sin(a) * x + 0 * y + cos(a) * z

# define R_ZX(x, y ,z, a) cos(a) * x + -sin(a) * y + 0 * z
# define R_ZY(x, y ,z, a) sin(a) * x + cos(a) * y + 0 * z
# define R_ZZ(x, y ,z, a) 0 * x + 0 * y + 1 * z

# define P_OX(x, y, z) x * 1 + y * 0 + z * 0 + 1 * 0
# define P_OY(x, y, z) x * 0 + y * 1 + z * 0 + 1 * 0
# define P_OZ(x, y, z) x * 0 + y * 0 + z * 0 + 1 * 0

# define P_PRX(x, y, z, f, fa, ne) x * (1 / (tan(f / 2 * (M_PI / 180)))) + 0 * y + 0 * z + 1 * 0
# define P_PRY(x, y, z, f, fa, ne) x * 0 + y * (1 / (tan(f / 2 * (M_PI / 180)))) + 0 * z + 1 * 0
# define P_PRZ(x, y, z, f, fa, ne) x * 0 + y * 0 + z * -(fa/ (fa - ne)) -1

# define P_PAX(x, y, z, f, n) x * 1 + y * 0 + z * n * cos(f)
# define P_PAY(x, y, z, f, n) x * 0 + y * 1 + z * n * cos(f)
# define P_PAZ(x, y, z, f, n) x * 0 + y * 0 + z * 0


# include <math.h>
# include "mlx.h"
# include "libft.h"


typedef struct	s_vec3
{
	double x;
	double y;
	double z;
	double w;
}				t_vec3;

typedef struct s_data
{
	void *mlx_ptr;
	void *mlx_win;
	int width;
	int length;
	t_vec3 **pnt;
	int lenx;
	int leny;
}				t_data;

typedef struct	s_size
{
	int x;
	int y;
}				t_size;

t_vec3 **proj_ortho(t_vec3 **pnt, int lenx, int leny);

void		draw_line(t_data *data, int start[2], int end[2], int col);
t_vec3	**file_manager(int fd, int *lenx, int *leny);
t_vec3 **transform_move(t_data data, double x, double y, double z);
t_vec3 **transform_scale(t_data data, double x, double y, double z);
t_vec3 **move_y(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **move_z(t_vec3 **pnt, double num, int lenx, int leny);

t_vec3 **scale_x(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **scale_y(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **scale_z(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **scale_xyz(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **rotate_x(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **rotate_y(t_vec3 **pnt, double num, int lenx, int leny);
t_vec3 **rotate_z(t_vec3 **pnt, double num, int lenx, int leny);
void	draw_3d_grid(t_data *data, t_vec3 **point, int lenx, int leny);
t_vec3	**proj_perspective(t_vec3 **pnt, int fov,int lenx, int leny);
t_vec3	**proj_parallel(t_vec3 **pnt, int fov, int lenx, int leny);
void		error_manager(char *str);
t_vec3	matrix_multiply_4(t_vec3 r, double **m);

#endif
