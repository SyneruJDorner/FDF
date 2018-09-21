/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mian.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 06:55:31 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/27 11:43:04 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define EXIT 17
#define EXPOSE 12

int		expose_hook(t_mlx *mlx)
{
	drawgui(mlx);
	return (0);
}

int		exit_hook(void)
{
	exit(0);
	return (0);
}

void	initializemlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WINWIDTH, WINHEIGHT, WINNAME);
	mlx->mouse.position.x = 0;
	mlx->mouse.position.y = 0;
	mlx->mouse.lastposition.x = 0;
	mlx->mouse.lastposition.y = 0;
	mlx->mouse.ismoving = FALSE;
	mlx->mouse.isleftdown = FALSE;
	mlx->mouse.isrightdown = FALSE;
	mlx->mouse.isleftdragging = FALSE;
	mlx->mouse.isrightdragging = FALSE;
	mlx->mouse.scrolldirection = -1;
	mlx->keyboard.keycode = -1;
	mlx->keyboard.extendedinputkey = -1;
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		readret;
	t_list	*readcontents;

	if (argc != 2 || !(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (FAILED);
	if (readmap(argc, argv, mlx) == -1)
		return (FAILED);
	initializemlx(mlx);
	initimage(mlx);
	initmouse(mlx);
	initkeyboard(mlx);
	mlx_hook(mlx->window, EXIT, 0, &exit_hook, mlx);
	mlx_hook(mlx->window, EXPOSE, 0, &expose_hook, mlx);
	drawgui(mlx);
	mlx_loop(mlx->mlx);
	return (PASS);
}
