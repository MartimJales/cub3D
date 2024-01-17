/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2024/01/13 15:28:36 by mjales           ###   ########.fr       */
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
	if (keycode == KEY_UP_M || keycode == KEY_W)
	{
		vars()->player->y += vars()->player->delta_y;
		vars()->player->x += vars()->player->delta_x;
	}
	else if (keycode == KEY_DOWN_M || keycode == KEY_S)
	{
		vars()->player->y -= vars()->player->delta_y;
		vars()->player->x -= vars()->player->delta_x;
	}
}

void	handle_rotation(int keycode)
{
	if (keycode == KEY_RIGHT_M || keycode == KEY_D)
	{
		vars()->player->angle += 0.1;
		if (vars()->player->angle > 2 * PI)
			vars()->player->angle -= 2 * PI;
		vars()->player->delta_x = cos(vars()->player->angle) * 5;
		vars()->player->delta_y = sin(vars()->player->angle) * 5;
	}
	else if (keycode == KEY_LEFT_M || keycode == KEY_A)
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
	handle_exit(keycode);
	handle_rotation(keycode);
	handle_movement(keycode);
	return (0);
}

int	render_hook()
{
	t_pos	pos2;

	pos2.color = vars()->ccolor;
	pos2.x=0;
	pos2.y=0;
	draw_rectagle(SCREENWIDTH, SCREENHEIGHT/3, pos2);
	pos2.y = SCREENHEIGHT/3;
	pos2.color = vars()->fcolor;
	draw_rectagle(SCREENWIDTH, 2*SCREENHEIGHT/3, pos2);

	draw_rays_2d(*vars()->win);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
	vars()->canvas.img_ptr,0, 0);
	return (0);
}

int	exit_program(void)
{
	mlx_destroy_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
	free(vars()->win->mlx_ptr);
	exit(0);
}
