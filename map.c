/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 07:30:11 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/27 11:35:06 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	*calculatevectorpoint(int x, int y, char *z)
{
	t_vector3	*point;

	if ((point = malloc(sizeof(t_vector3))) == NULL)
		return (NULL);
	point->x = (double)x;
	point->y = (double)y;
	point->z = (z == '\0') ? 0 : ft_atoi(z);
	return (point);
}

int			cleansplit(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	str = *split;
	while (*str)
	{
		ft_strdel(str);
		i++;
		str = &(*split)[i];
	}
	ft_memdel((void **)split);
	return (0);
}

void		calculatepoints(t_mlx *mlx, t_list *lst)
{
	t_map	*map;
	char	**split;
	int		x;
	int		y;

	map = mlx->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		if ((split = ft_strsplit(lst->content, ' ')) == NULL)
			return ;
		while (x < map->width)
		{
			map->vectors[y * map->width + x] =
				calculatevectorpoint(x, y, split[x]);
			x++;
		}
		cleansplit(&split);
		if (lst->next != NULL)
			lst = lst->next;
		y++;
	}
	mlx->map->scale /= x;
}

int			setmap(t_mlx *mlx, t_list *lst, int width, int height)
{
	if (!(mlx->map = malloc(sizeof(t_map))))
		return (-1);
	mlx->map->width = width;
	mlx->map->height = height;
	mlx->map->position.x = WINWIDTH / 2;
	mlx->map->position.y = WINHEIGHT / 2;
	mlx->map->position.z = 0;
	mlx->map->rotationx = 0;
	mlx->map->rotationy = 0;
	mlx->map->scale = 500;
	mlx->map->depth = 1;
	mlx->map->mindepth = -2;
	mlx->map->maxdepth = 2;
	if (!(mlx->map->vectors = malloc(sizeof(t_vector3 *) * width * height)))
		return (-1);
	calculatepoints(mlx, lst);
	return (0);
}
