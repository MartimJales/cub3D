/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:18 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 18:55:44 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	handle_movement(int keycode)
{
	int	teste_x;
	int	teste_y;

	if (keycode == KEY_UP_M || keycode == KEY_W)
	{
		teste_x = (vars()->player->x + vars()->player->delta_x * 10) / CUBESIZE;
		teste_y = (vars()->player->y + vars()->player->delta_y * 10) / CUBESIZE;
		if (vars()->map[teste_y][teste_x] == 0)
		{
			vars()->player->x += vars()->player->delta_x;
			vars()->player->y += vars()->player->delta_y;
		}
	}
	else if (keycode == KEY_DOWN_M || keycode == KEY_S)
	{
		teste_x = (vars()->player->x - vars()->player->delta_x * 10) / CUBESIZE;
		teste_y = (vars()->player->y - vars()->player->delta_y * 10) / CUBESIZE;
		if (vars()->map[teste_y][teste_x] == 0)
		{
			vars()->player->y -= vars()->player->delta_y;
			vars()->player->x -= vars()->player->delta_x;
		}
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

int	render_hook(void)
{
	t_pos	pos2;

	pos2.color = vars()->ccolor;
	pos2.x = 0;
	pos2.y = 0;
	draw_rectagle(SCREENWIDTH, SCREENHEIGHT / 2, pos2);
	pos2.y = SCREENHEIGHT / 2;
	pos2.color = vars()->fcolor;
	draw_rectagle(SCREENWIDTH, SCREENHEIGHT / 2, pos2);
	draw_rays_2d(*vars()->win);
	mlx_put_image_to_window(vars()->win->mlx_ptr, vars()->win->win_ptr, \
	vars()->canvas.img_ptr, 0, 0);
	return (0);
}

int	exit_program(int exit_status)
{
	if (vars()->win->mlx_ptr)
	{
		if (vars()->canvas.img_ptr)
			mlx_destroy_image(vars()->win->mlx_ptr, vars()->canvas.img_ptr);
		if (vars()->no.img_ptr)
			mlx_destroy_image(vars()->win->mlx_ptr, vars()->no.img_ptr);
		if (vars()->so.img_ptr)
			mlx_destroy_image(vars()->win->mlx_ptr, vars()->so.img_ptr);
		if (vars()->ea.img_ptr)
			mlx_destroy_image(vars()->win->mlx_ptr, vars()->ea.img_ptr);
		if (vars()->we.img_ptr)
			mlx_destroy_image(vars()->win->mlx_ptr, vars()->we.img_ptr);
		mlx_destroy_window(vars()->win->mlx_ptr, vars()->win->win_ptr);
		mlx_destroy_display(vars()->win->mlx_ptr);
		free(vars()->win->mlx_ptr);
	}
	exit(exit_status);
}
