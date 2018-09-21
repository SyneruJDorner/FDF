/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybaord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 07:09:40 by jdorner           #+#    #+#             */
/*   Updated: 2018/07/24 12:07:39 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define KEY_BEGIN 2
#define KEY_END 3

int		key_begin(int key, t_mlx *mlx)
{
	t_keycode keycode;

	keycode = key;
	if (key == LEFTCMD)
		mlx->keyboard.extendedinputkey = LEFTCMD;
	mlx->keyboard.keycode = key;
	drawgui(mlx);
	if (keycode == ESCAPE)
		exit(0);
	return (0);
}

int		key_end(int key, t_mlx *mlx)
{
	t_keycode	keycode;

	keycode = key;
	if (mlx->keyboard.keycode >= 0)
		mlx->keyboard.keycode = -1;
	mlx->keyboard.extendedinputkey = -1;
	drawgui(mlx);
	return (0);
}

void	initkeyboard(t_mlx *mlx)
{
	mlx_hook(mlx->window, KEY_BEGIN, 0, &key_begin, mlx);
	mlx_hook(mlx->window, KEY_END, 0, &key_end, mlx);
}
