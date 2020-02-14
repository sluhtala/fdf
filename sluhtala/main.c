/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:03:00 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/14 17:05:03 by sluhtala         ###   ########.fr       */
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
int expand_lines(t_data *data, double num)
{
	static double x = 0;
	int p1[2] = {data->width / 2, data->length / 2}; 
	int p2[2] = {p1[0] * 2, p1[1]};
	int dist = sqrt((data->width / 2) * (data->width / 2) + (data->length / 2) * (data->length / 2));
	
	x += num;
	if (x >= 360)
		x = 0;
	if (x < 0)
		x = 359;
	//mlx_clear_window(data->mlx_ptr, data->mlx_win);
	p2[0] = data->width / 2 + cos(x * M_PI / 180) * dist;
	p2[1] = data->length / 2 - sin(x * M_PI / 180) * dist;
	draw_line(data, p1, p2, 0xffffff);
	return (0);
}

int		input_manager(int key, t_data *data)
{
	printf("%d\n", key);
	if (key == esc_key || key == 12)
		close_program(data);
	if (key == up_key)
		expand_lines(data, -5);
	if (key == down_key)
		expand_lines(data, 5);
	if (key == 18)
	{
		printf("parallel\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		*data->pnt = proj_parallel(*data->pnt, 50 * (M_PI/180), data->lenx, data->leny);
		draw_3d_grid(data, *data->pnt, data->lenx, data->leny);
	}
	if (key == 19)
	{
		printf("perspective\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		*data->pnt = proj_perspective(*data->pnt, 80, data->lenx, data->leny);
		draw_3d_grid(data, *data->pnt, data->lenx, data->leny);
	}
	if (key == 20)
	{
		printf("perspective\n");
		mlx_clear_window(data->mlx_ptr, data->mlx_win);
		*data->pnt = proj_perspective(*data->pnt, 110, data->lenx, data->leny);
		draw_3d_grid(data, *data->pnt, data->lenx, data->leny);
	}
	return (key);
}

void print_map(t_coord3d **map, int lenx, int leny)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while(y < leny)
	{
		i = 0;
		while (i < lenx)
		{
			printf("x: %2f y:%2f z: %2f\n", map[y][i].x, map[y][i].y, map[y][i].z);
			i++;
		}
		y++;
		printf("\n");
	}

}

int		main(int argc, char **argv)
{
	t_data d;
	t_data *data;
	t_size map_size;

	t_coord3d **points;
	int fd;

	if (argc != 2)
		return (0);
	if (!(fd = open(argv[1], O_RDONLY)))
		return (0);
	d.width = 1920 / 2;
	d.length = 1080 /2 ;

	points = file_manager(fd, &map_size.x, &map_size.y);
	printf("x:%d y:%d\n", map_size.x, map_size.y);
	points = scale_x(points, 2, map_size.x, map_size.y);
	points = scale_y(points, 2 ,map_size.x, map_size.y);
	points = scale_z(points, 5, map_size.x, map_size.y);
	points = rotate_z(points, 45 * (M_PI / 180)  , map_size.x, map_size.y);
	points = rotate_x(points, 45 * (M_PI / 180)  , map_size.x, map_size.y);
	//points = rotate_y(points, 20 * (M_PI / 180)  , map_size.x, map_size.y);
	points = proj_perspective(points, 60, map_size.x, map_size.y);
	points = move_x(points, 300, map_size.x, map_size.y);
	points = move_y(points, 100, map_size.x, map_size.y);
	//points = rotate_x(points, 30 * (M_PI / 180) , map_size.x, map_size.y);
	print_map(points, map_size.x, map_size.y);
	d.pnt = &points;
	d.lenx = map_size.x;
	d.leny = map_size.y;
	
	//points = proj_ortho(points, map_size.x, map_size.y);
	
	data = &d;
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_win = mlx_new_window(data->mlx_ptr, data->width, data->length, "FDF")))
		return (-1);
	draw_3d_grid(data, points, map_size.x, map_size.y);
	mlx_hook(data->mlx_win, 2, 0, &input_manager, data);
	mlx_loop(data->mlx_ptr);
	
	return (0);
}
