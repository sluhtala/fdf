/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:28:23 by sluhtala          #+#    #+#             */
/*   Updated: 2020/02/18 18:39:38 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static void		free_splitted(char ***split)
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

static int		split_len(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static t_vec3	*make_points(t_vec3 **pnt, char **map,
		int *lenx, int y)
{
	char	**temp;
	int		len;
	int		i;

	i = 0;
	while ((*map)[i] != '\n' && (*map)[i])
		i++;
	(*map)[i] = '\0';
	temp = ft_split(*map);
	*map = *map + i + 1;
	if ((len = split_len(temp)) != *lenx && *lenx != 0)
		error_manager("Not valid map.");
	*lenx = len;
	if (!(pnt[y] = (t_vec3*)malloc(sizeof(t_vec3) * *lenx)))
		error_manager("Malloc error.");
	i = 0;
	while (i < *lenx)
	{
		pnt[y][i].x = (double)i;
		pnt[y][i].y = (double)y;
		pnt[y][i].z = (double)ft_atoi(temp[i]);
		pnt[y][i].w = 1;
		i++;
	}
	free_splitted(&temp);
	return (pnt[y]);
}

static t_vec3	**get_coords(char *map, int *xlen, int *ylen)
{
	t_vec3	**points;
	int			y;

	y = 0;
	*ylen = 0;
	*xlen = 0;
	while (map[y])
	{
		if (map[y] == '\n')
			*ylen = *ylen + 1;
		y++;
	}
	points = (t_vec3**)malloc(sizeof(t_vec3*) * *ylen);
	y = 0;
	while (y < *ylen)
	{
		points[y] = make_points(points, &map, xlen, y);
		y++;
	}
	return (points);
}

t_vec3			**file_manager(int fd, int *lenx, int *leny)
{
	char		*map;
	char		*temp;
	char		buf[42 + 1];
	int			ret;
	t_vec3	**points;

	map = ft_strnew(1);
	while ((ret = read(fd, buf, 42)) > 0)
	{
		temp = map;
		buf[ret] = '\0';
		map = ft_strjoin(map, buf);
		free(temp);
	}
	points = get_coords(map, lenx, leny);
	free(map);
	map = NULL;
	return (points);
}
