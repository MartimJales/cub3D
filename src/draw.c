/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:38:23 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 16:24:13 by dcordovi         ###   ########.fr       */
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
	vars()->line_h = (CUBESIZE * SCREENHEIGHT / vars()->dist);
	vars()->ty_step = CUBESIZE / vars()->line_h;
	vars()->ty_off = 0;
	if (vars()->line_h > SCREENHEIGHT)
	{
		vars()->ty_off = (vars()->line_h - SCREENHEIGHT) / 2;
		vars()->line_h = SCREENHEIGHT;
	}
	(void) pos;
	vars()->ra += vars()->dr;
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
		vars()->tx = (int)(vars()->ry) % CUBESIZE;
		vars()->shade = 0.5;
	}
	else
		vars()->tx = (int)(vars()->rx) % CUBESIZE;
	vars()->disth *= cos(vars()->ca);
	vars()->pix_size = 1;
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
		get_pixel_img(wall, (int)(vars()->tx) + (int)(vars()->ty) * CUBESIZE);
		pos.x = vars()->r * vars()->pix_size;
		pos.y = SCREENHEIGHT / 2 - vars()->line_h / 2 + y;
		pos.color = color * vars()->shade;
		draw_rectagle(vars()->pix_size, vars()->pix_size, pos);
		vars()->ty += vars()->ty_step;
		y++;
	}
}
