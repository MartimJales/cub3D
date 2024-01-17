/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:38:23 by mjales            #+#    #+#             */
/*   Updated: 2024/01/15 11:03:57 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	draw_3d_aux1(t_pos pos)
{
	vars()->ca = vars()->player->angle - vars()->ra;
	if (vars()->ca < 0)
		vars()->ca += 2 * PI;
	if (vars()->ca > 2 * PI)
		vars()->ca -= 2 * PI;
	vars()->dist = vars()->dist * cos(vars()->ca);
	vars()->line_h = (CUBESIZE * SCREEN2HEIGHT / vars()->dist);
	vars()->ty_step = 64.0 / vars()->line_h;
	vars()->ty_off = 0;
	if (vars()->line_h > SCREEN2HEIGHT)
	{
		vars()->ty_off = (vars()->line_h - SCREEN2HEIGHT) / 2;
		vars()->line_h = SCREEN2HEIGHT;
	}
	(void) pos;
	vars()->ra += DR;
	if (vars()->ra < 0)
		vars()->ra += 2 * PI;
	if (vars()->ra >= 2 * PI)
		vars()->ra -= 2 * PI;
	vars()->ty = vars()->ty_off * vars()->ty_step;
	vars()->shade = 1;
}

void	draw_3d_aux2(void)
{
	if (vars()->disth >= vars()->distv)
	{
		vars()->tx = (int)(vars()->ry) % 64;
		vars()->shade = 0.5;
	}
	else
		vars()->tx = (int)(vars()->rx) % 64;
	vars()->disth *= cos(vars()->ca);
	vars()->pix_size = SCREENWIDTH / RAYNBR;
}

t_img	get_wall_img(void)
{
	if (vars()->disth >= vars()->distv)
	{
		if (vars()->rx < vars()->player->x)
			return (vars()->we);
		return (vars()->ea);
	}
	else
	{
		if (vars()->ry < vars()->player->y)
			return (vars()->so);
		return (vars()->no);
	}
}

void	draw_3d_walls(void)
{
	int			y;
	t_pos		pos;
	int			color;
	t_img		wall;

	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = gen_trgb(255, 0, 255, 0);
	draw_3d_aux1(pos);
	wall = get_wall_img();
	draw_3d_aux2();
	y = 0;
	while (y < vars()->line_h)
	{
		color = \
		get_pixel_img(wall, (int)(vars()->tx) + (int)(vars()->ty) * 64);
		pos.x = vars()->r * vars()->pix_size;
		pos.y = SCREEN2HEIGHT / 2 - vars()->line_h / 2 + y;
		pos.color = color * vars()->shade;
		draw_rectagle(vars()->pix_size, vars()->pix_size, pos);
		vars()->ty += vars()->ty_step;
		y++;
	}
}

void	draw_rays_2d(t_win window)
{
	double	ra;

	init_vars();
	vars()->r = 0;
	ra = vars()->ra;
	while (vars()->r < RAYNBR)
	{
		ra = vars()->ra;
		horizontal_check(ra);
		vertical_check(ra);
		wall_color();
		draw_3d_walls();
		vars()->r++;
	}
	(void)window;
}

void	draw_player_and_rays(t_win window, t_img player_img)
{
	initialize_player_position();
	 (void) player_img;
	draw_rays_2d(window);
}
