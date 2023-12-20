/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2023/12/20 15:27:32 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	handle_exit(int keycode)
{
	if (keycode == ESC_KEY_M || keycode == CROSS)
	{
		exit_program();
	}
}

void	handle_movement(int keycode)
{
	if (keycode == KEY_UP_M)
	{
		vars()->player->y += vars()->player->delta_y;
		vars()->player->x += vars()->player->delta_x;
	}
	else if (keycode == KEY_DOWN_M)
	{
		vars()->player->y -= vars()->player->delta_y;
		vars()->player->x -= vars()->player->delta_x;
	}
}

void	handle_rotation(int keycode)
{
	if (keycode == KEY_RIGHT_M)
	{
		vars()->player->angle += 0.1;
		if (vars()->player->angle > 2 * PI)
			vars()->player->angle -= 2 * PI;
		vars()->player->delta_x = cos(vars()->player->angle) * 5;
		vars()->player->delta_y = sin(vars()->player->angle) * 5;
	}
	else if (keycode == KEY_LEFT_M)
	{
		vars()->player->angle -= 0.1;
		if (vars()->player->angle < 0)
			vars()->player->angle += 2 * PI;
		vars()->player->delta_x = cos(vars()->player->angle) * 5;
		vars()->player->delta_y = sin(vars()->player->angle) * 5;
	}
}

int	key_hook(int keycode)
{
	t_position	pos;

	handle_exit(keycode);
	handle_rotation(keycode);
	handle_movement(keycode);
	mlx_clear_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = gen_trgb(0, 255, 255, 0);
	draw_player(vars()->player->img, PLAYERSIZE, pos);
	draw_rays_2d(*vars()->win);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
	vars()->player->img.img_ptr, vars()->player->x, vars()->player->y);
	return (0);
}

// mlx_destroy_image(vars()->win->mlx_ptr, vars()->img_ptr->img_ptr);
//mlx_destroy_display(vars()->win->mlx_ptr);
int	exit_program(void)
{
	mlx_destroy_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	free(vars()->win->mlx_ptr);
	exit(0);
}
