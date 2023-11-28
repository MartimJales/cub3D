/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2023/11/28 11:49:28 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	key_hook(int keycode, t_var *v)
{
	(void)v;
	// printf("keycode = %d\n", keycode);
	if (keycode == ESC_KEY_M || keycode == CROSS)
	{
		exit_program(vars());
	}
	else if (keycode == KEY_RIGHT_M)
	{
		// vars()->player->x += 5;
		vars()->player->angle += 0.1;
		if (vars()->player->angle > 2 * PI)
			vars()->player->angle -= 2 * PI;
		vars()->player->deltaX = cos(vars()->player->angle)*5;
		vars()->player->deltaY = sin(vars()->player->angle)*5;
	}
	else if (keycode == KEY_LEFT_M){
		// vars()->player->x -= 5;
		vars()->player->angle -= 0.1;
		if (vars()->player->angle < 0)
			vars()->player->angle += 2 * PI;
		vars()->player->deltaX = cos(vars()->player->angle)*5;
		vars()->player->deltaY = sin(vars()->player->angle)*5;
	}
	else if(keycode == KEY_UP_M)
	{
		// vars()->player->y -= 5;
		vars()->player->y += vars()->player->deltaY;
		vars()->player->x += vars()->player->deltaX;
	}
	else if (keycode == KEY_DOWN_M)
	{
		// vars()->player->y += 20;
		vars()->player->y -= vars()->player->deltaY;
		vars()->player->x -= vars()->player->deltaX;
	}
	mlx_clear_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
		// Draw ceil_img
	// mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->ceil_img.img_ptr, screenWidth/2, 0);
	// Draw floor_img
	// mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->floor_img.img_ptr, screenWidth/2, screenHeight/3);

	draw_map();
	// draw_player(vars()->player->img, playerSize, gen_trgb(0, 255, 255, 0), vars()->player->x, vars()->player->y);

	drawRays2D(*vars()->win);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
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
	// mlx_destroy_image(vars()->win->mlx_ptr, vars()->img_ptr->img_ptr);
	mlx_destroy_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	//mlx_destroy_display(vars()->win->mlx_ptr);
	free(vars()->win->mlx_ptr);
	exit(0);
}
