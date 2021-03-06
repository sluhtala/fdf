/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:32:04 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/26 13:48:50 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESC_KEY 53
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define SPACE_KEY 49
# define SCREENCENTER_X data->width / 2
# define SCREENCENTER_Y data->length / 2

# include <math.h>
# include "mlx.h"
# include "libft.h"

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
	double	w;
	int		color;
}				t_vec3;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		length;
	t_vec3	**pnt;
	t_vec3	**pnt_cpy;
	int		lenx;
	int		leny;
	int		img_posx;
	int		img_posy;
	int		scale;
}				t_data;

t_vec3			**proj_ortho(t_vec3 **pnt, int lenx, int leny);
void			draw_line(t_data *data, int start[2], int end[2],
		double col[2]);
void			free_pnt(t_data *data);
t_vec3			**copy_pnt(t_data *data);
t_vec3			**set_color(t_data *data);
t_vec3			**file_manager(int fd, int *lenx, int *leny);
t_vec3			**transform_move(t_data data, double x, double y, double z);
t_vec3			**transform_scale(t_data data, double x, double y, double z);
t_vec3			**transform_rotate_x(t_data data, double a);
t_vec3			**transform_rotate_y(t_data data, double a);
t_vec3			**transform_rotate_z(t_data data, double a);
double			**make_xmatrix(double a);
double			**make_ymatrix(double a);
double			**make_zmatrix(double a);
t_vec3			**transform_perspective(t_data data, double fov);
void			draw_grid(t_data *data);
void			error_manager(char *str);
t_vec3			matrix_multiply_4(t_vec3 r, double **m);
double			**matrix_alloc(void);
t_vec3			**normalize_pnt(t_data data);
t_vec3			**transformation(t_data *datai);

#endif
