/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:03:00 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/20 18:38:25 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

int		close_program(t_data *data)
{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	return (0);
}

#include <stdio.h>

t_vec3 **normalize_pnt(t_data data)
{
	int i;
	int y;
	double d;

	y = 0;
	while (y < data.leny)
	{
		i = 0;
		while (i < data.lenx)
		{
			d = sqrt(data.pnt[y][i].x * data.pnt[y][i].x + data.pnt[y][i].y * data.pnt[y][i].y);
			if (d != 0)
			{
				data.pnt[y][i].x = data.pnt[y][i].x / d;
				data.pnt[y][i].y = data.pnt[y][i].y / d;
				data.pnt[y][i].z = data.pnt[y][i].z / d;
			}
			i++;
		}
		y++;
	}
	return (data.pnt);
}

static t_vec3 **raster(t_vec3 **pnt, t_data data)
{
	int i;
	int y;
	double w;
	double l;

	w = data.width;
	l = data.length;
	y = 0;
	while (y < data.leny)
	{
		i = 0;
		while (i < data.lenx)
		{
			pnt[y][i].x = pnt[y][i].x * (w / l);
			pnt[y][i].y = pnt[y][i].y * (w / l);
			pnt[y][i].z = pnt[y][i].z * (w / l);
			i++;
		}
		y++;
	}
	return (pnt);
}
t_vec3 **transformation(t_data *data)
{	
	data->pnt = set_color(data);	
	//data->pnt = transform_rotate_y(*data, 42*(M_PI/180));
	//data->pnt = transform_rotate_z(*data, 42*(M_PI/180));
	//data->pnt = transform_scale(*data, 40, 40, 0.5);
	//data->pnt = normalize_pnt(*data);
	data->pnt = transform_scale(*data, 30, 10, 0.8);
	data->pnt = transform_rotate_x(*data, 20 * (M_PI / 180));
	//data->pnt = normalize_pnt(*data);
	data->pnt = transform_rotate_y(*data, 20 * (M_PI / 180));
	data->pnt = transform_move(*data, 140, 140, -60);
	data->pnt = transform_perspective(*data, 90);
	//data->pnt = raster(data->pnt, *data);
	return (data->pnt);
}

static t_vec3	**move(int key, t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	if (key == up_key)
		data->pnt = transform_move(*data, 0, -40, 0);
	if (key == down_key)
		data->pnt = transform_move(*data, 0, 40, 0);
	if (key == right_key)
		data->pnt = transform_move(*data, 40, 0, 0);
	if (key == left_key)
		data->pnt = transform_move(*data, -40, 0, 0);
	draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	return (data->pnt);
}
int		input_manager(int key, t_data *data)
{
	printf("%d\n", key);
	double cent1;
	double cent2;
	double cent3;

	cent1 = ((data->pnt[0][0].x + data->pnt[data->leny - 1][data->lenx - 1].x )/ 2);
	cent2 = ((data->pnt[0][0].y + data->pnt[data->leny - 1][data->lenx - 1].y )/ 2);
	cent3 = ((data->pnt[0][0].z + data->pnt[data->leny - 1][data->lenx - 1].z )/ 2);
	if (key == esc_key || key == 12)
		close_program(data);
	if (key == up_key || key == down_key || key == right_key || key == left_key)
		data->pnt = move(key, data);
	if (key == 18)
	{
		printf("Scale down\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		//data->pnt = transform_move(*data, -cent1, -cent2, -cent3);
		data->pnt = transform_scale(*data, 0.8, 0.8, 0.8);
		//data->pnt = transform_move(*data, cent1, cent2, cent3);
		draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	}
	if (key == 19)
	{
		printf("Scale up\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		//data->pnt = transform_move(*data, -cent1, -cent2, -cent3);
		data->pnt = transform_scale(*data, 1.2, 1.2, 1.2);
		//data->pnt = transform_move(*data, cent1, cent2, cent3);
		draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	}
	if (key == 20)
	{
		printf("perspective\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		data->pnt = proj_perspective(data->pnt, 110, data->lenx, data->leny);
		draw_3d_grid(data, data->pnt, data->lenx, data->leny);
	}
	return (key);
}

int		main(int argc, char **argv)
{
	t_data d;
	t_data *data;
	t_size map_size;
	int fd;

	data = &d;
	if (argc != 2)
		return (0);
	if (!(fd = open(argv[1], O_RDONLY)))
		return (0);
	d.width = 1920 / 2;
	d.length = 1080 /2 ;
	d.pnt = file_manager(fd, &d.lenx, &d.leny); // Gets points from file 
	//data->pnt = set_color(data);
	data->pnt = transformation(data);	// does all transformations to points and handles the colors
	//print_map(d.pnt, d.lenx, d.leny);
	//print_map(d.pnt, d.lenx, d.leny);
	data->mlx_ptr = mlx_init(); // initialize mlx
	if (!(data->mlx_win = mlx_new_window(data->mlx_ptr, data->width, data->length, "FDF"))) // new window
		return (-1);
	draw_3d_grid(data, data->pnt, d.lenx, d.leny); // renderer.. draws lines from point to point. 
	mlx_hook(data->mlx_win, 2, 0, &input_manager, data);
	mlx_loop(data->mlx_ptr);
	
	return (0);
}
