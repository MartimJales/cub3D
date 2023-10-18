/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2023/10/18 17:42:59 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	key_hook(int keycode, t_var *v)
{
	(void)v;
	if (keycode == ESC_KEY || keycode == CROSS)
	{
		exit_program(vars());
	}
	else if(keycode == KEY_UP)
	{
		printf("KEY_UP\n");
		if(vars()->worldMap[(int)(vars()->posX + vars()->dirX * vars()->moveSpeed)][(int)vars()->posY] == 0) vars()->posX += vars()->dirX * vars()->moveSpeed;
		if(vars()->worldMap[(int)vars()->posX][(int)(vars()->posY + vars()->dirY * vars()->moveSpeed)] == 0) vars()->posY += vars()->dirY * vars()->moveSpeed;
	}
	else if (keycode == KEY_DOWN)
	{
		printf("KEY_DOWN\n");
		if(vars()->worldMap[(int)(vars()->posX - vars()->dirX * vars()->moveSpeed)][(int)vars()->posY] == 0) vars()->posX -= vars()->dirX * vars()->moveSpeed;
		if(vars()->worldMap[(int)vars()->posX][(int)(vars()->posY - vars()->dirY * vars()->moveSpeed)] == 0) vars()->posY -= vars()->dirY * vars()->moveSpeed;
	}
	else if (keycode == KEY_RIGHT)
	{
		printf("KEY_RIGHT\n");
		double oldDirX = vars()->dirX;
		vars()->dirX = vars()->dirX * cos(-vars()->rotSpeed) - vars()->dirY * sin(-vars()->rotSpeed);
		vars()->dirY = oldDirX * sin(-vars()->rotSpeed) + vars()->dirY * cos(-vars()->rotSpeed);
		double oldPlaneX = vars()->planeX;
		vars()->planeX = vars()->planeX * cos(-vars()->rotSpeed) - vars()->planeY * sin(-vars()->rotSpeed);
		vars()->planeY = oldPlaneX * sin(-vars()->rotSpeed) + vars()->planeY * cos(-vars()->rotSpeed);
	}
	else if (keycode == KEY_LEFT)
	{
		printf("KEY_LEFT\n");
		double oldDirX = vars()->dirX;
		vars()->dirX = vars()->dirX * cos(vars()->rotSpeed) - vars()->dirY * sin(vars()->rotSpeed);
		vars()->dirY = oldDirX * sin(vars()->rotSpeed) + vars()->dirY * cos(vars()->rotSpeed);
		double oldPlaneX = vars()->planeX;
		vars()->planeX = vars()->planeX * cos(vars()->rotSpeed) - vars()->planeY * sin(vars()->rotSpeed);
		vars()->planeY = oldPlaneX * sin(vars()->rotSpeed) + vars()->planeY * cos(vars()->rotSpeed);
	}
	mlx_clear_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	paint_cub3D();
	return (0);
}

int	mouse_hook(int keycode)
{
	// if (keycode == SCROLL_UP)
	// 	zoom_in(vars()());
	// else if (keycode == SCROLL_DOWN)
	// 	zoom_out(vars()());
	return (keycode);
}

int	exit_program(t_var *v)
{
	(void)v;
	mlx_destroy_image(vars()->win->mlx_ptr, vars()->img_ptr->img_ptr);
	mlx_destroy_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	mlx_destroy_display(vars()->win->mlx_ptr);
	free(vars()->win->mlx_ptr);
	exit(0);
}
