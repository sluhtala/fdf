/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:28:23 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/13 16:45:59 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static void	free_splitted(char ***split)
{
	int i;

	if (!(*split))
		return ;
	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
}

int		split_len(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

#include <stdio.h>
int **make_map(char *str, int len, int *lenx, int *leny)
{
	int **map;
	char **split;
	int i;
	int y;

	*leny = ft_strlen(str) / len;
	map = (int**)malloc(sizeof(int*) * *leny);
	y = 0;
	while (y < *leny)
	{
		i = 0;
		if (y != 0)
			str[y - 1 * len] = '\0';
		split = ft_split(str + y * len);
		*lenx = split_len(split);
		map[y] = (int*)malloc(sizeof(int) * *lenx); 
		while (split[i])
		{
			map[y][i] = ft_atoi(split[i]);	
			i++;
		}
		y++;
		free_splitted(&split);
	}
	return (map);
}

int **get_map(int fd, int *lenx, int *leny)
{
	char *line;
	char *temp;
	char *temp2;
	int len;

	temp2 = ft_strnew(1);
	while (get_next_line(fd, &line))
	{
		len = ft_strlen(line) + 1;	
		temp = ft_strjoin(temp2, line);
		free(temp2);
		free(line);
		temp2 = ft_strjoin(temp, " ");
		free(temp);
	}
	
	//if (ft_strlen(temp2) / len * len != ft_strlen(temp2))
	//	return (NULL);
	return (make_map(temp2, len, lenx, leny));
}


t_coord3d **get_coords(int **map, int xlen, int ylen)
{
	t_coord3d **points;
	int i;
	int y;
	int m = 10;

	i = 0;
	y = 0;
	points = (t_coord3d**)malloc(sizeof(t_coord3d*) * ylen);
	while (i < ylen)
	{
		points[i] = (t_coord3d*)malloc(sizeof(t_coord3d) * xlen);
		i++;
	}
	while (y < ylen)
	{
		i = 0;
		while (i < xlen)
		{
			points[y][i].x = i * m;
			points[y][i].y = y * m;
			points[y][i].z = (double)map[y][i];
			i++;
		}
		y++;
	}
	return (points);
}

static void print_map(t_coord3d **map, int lenx, int leny)
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
t_coord3d 	**file_manager(int fd, int *lenx, int *leny)
{
	int **map;
	int i;
	int y;

	t_coord3d **points;
	map = get_map(fd, lenx, leny);
	points = get_coords(map, *lenx, *leny);
	i = 0;
	while (i < *leny)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
	print_map(points, *lenx, *leny);
	return (points);
}
