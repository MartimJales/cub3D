/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2023/10/30 17:04:07 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	key_hook(int keycode, t_var *v)
{
	(void)v;
	printf("keycode = %d\n", keycode);
	if (keycode == ESC_KEY_M || keycode == CROSS)
	{
		exit_program(vars());
	}
	else if(keycode == KEY_UP_M)
	{
		printf("KEY_UP\n");
		vars()->player->y += vars()->player->deltaY;
		vars()->player->x += vars()->player->deltaX;
	}
	else if (keycode == KEY_DOWN_M)
	{
		printf("KEY_DOWN\n");
		vars()->player->y -= vars()->player->deltaY;
		vars()->player->x -= vars()->player->deltaX;
	}
	else if (keycode == KEY_RIGHT_M)
	{
		printf("KEY_RIGHT\n");
		vars()->player->angle += 0.1;
	}
	else if (keycode == KEY_LEFT_M){
		printf("KEY_LEFT\n");
		vars()->player->angle -= 0.1;
	}
	vars()->player->deltaX = cos(vars()->player->angle) * 5;
	vars()->player->deltaY = sin(vars()->player->angle) * 5;

	// if (vars()->player->angle < 0)
	// 	vars()->player->angle += 2 * M_PI;
	// else if (vars()->player->angle > 2 * M_PI)
	// 	vars()->player->angle = 0;

	// if (x < 0 || y < 0 || x > screenWidth-vars()->player->size || y > screenHeight-vars()->player->size)
	// 	return (0);
	mlx_clear_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	draw_map();
	draw_player(vars()->player->img, playerSize, gen_trgb(0, 255, 255, 0), vars()->player->x, vars()->player->y); // aagar no fim qaundo tivermos os raios to ginjas
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
