/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 08:27:03 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/24 14:10:40 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ABS(N) ((N < 0) ? (-N) : (N))
#define SIGN(N) ((N == 0) ? 0 : ((N < 0) ? -1 : 1))
#define MAX(A, B) ((A > B) ? (A) : (B))

void	initimage(t_mlx *mlx)
{
	t_image	*img;

	if ((img = (t_image *)malloc(sizeof(t_image))) == NULL)
		return ;
	img->image = mlx_new_image(mlx->mlx, WINWIDTH, WINHEIGHT);
	img->ptr = mlx_get_data_addr(img->image,
								&img->bitsperpixel,
								&img->line_size,
								&img->endian);
	img->bitsperpixel /= 8;
	mlx->image = img;
}

void	putpixelimage(t_linevariables linevar, t_mlx *mlx)
{
	t_image	*img;

	img = mlx->image;
	if (linevar.x >= 0 && linevar.x < WINWIDTH
			&& linevar.y >= 0 && linevar.y < WINHEIGHT)
		*(int *)(img->ptr + ((linevar.x + linevar.y * WINWIDTH)
					* img->bitsperpixel)) = linevar.colour;
}

void	calculateline(t_linevariables linevar, t_mlx *mlx)
{
	int		i;

	i = -1;
	while (i++ < linevar.maxdist)
	{
		putpixelimage(linevar, mlx);
		if (linevar.distancex > linevar.distancey)
		{
			linevar.x += linevar.signx;
			if ((linevar.r += linevar.distancey) >= linevar.distancex)
			{
				linevar.y += linevar.signy;
				linevar.r -= linevar.distancex;
			}
		}
		else
		{
			linevar.y += linevar.signy;
			if ((linevar.r += linevar.distancex) >= linevar.signx)
			{
				linevar.x += linevar.signx;
				linevar.r -= linevar.distancey;
			}
		}
	}
}

void	drawline(t_mlx *mlx, t_vector3 from, t_vector3 to, int colour)
{
	t_linevariables	linevar;

	linevar.colour = colour;
	linevar.distancex = (to.x - from.x);
	linevar.distancey = (to.y - from.y);
	linevar.signx = SIGN(linevar.distancex);
	linevar.signy = SIGN(linevar.distancey);
	linevar.distancex = ABS(linevar.distancex);
	linevar.distancey = ABS(linevar.distancey);
	linevar.maxdist = MAX(linevar.distancex, linevar.distancey);
	linevar.r = linevar.maxdist / 2;
	linevar.x = from.x;
	linevar.y = from.y;
	calculateline(linevar, mlx);
}
