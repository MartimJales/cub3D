/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2023/12/05 16:16:10 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void handle_exit(int keycode)
{
	if (keycode == ESC_KEY_M || keycode == CROSS)
	{
		exit_program(vars());
	}
}

void handle_movement(int keycode)
{
	if(keycode == KEY_UP_M)
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
}

void handle_rotation(int keycode)
{
	if (keycode == KEY_RIGHT_M)
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
}

int key_hook(int keycode, t_var *v)
{
	(void)v;
    handle_exit(keycode);
    handle_rotation(keycode);
    handle_movement(keycode);
	mlx_clear_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	draw_map();
	draw_player(vars()->player->img, playerSize, gen_trgb(0, 255, 255, 0), vars()->player->x, vars()->player->y);

	drawRays2D(*vars()->win);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
	return (0);

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
