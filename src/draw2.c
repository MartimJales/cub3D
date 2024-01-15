/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:13:18 by mjales            #+#    #+#             */
/*   Updated: 2024/01/10 12:30:04 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	draw_square(t_img img, int size, t_pos pos)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_img(img, i + pos.x, j + pos.y, pos.color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_pos pos, int x1, int y1)
{
	line_vars(pos, x1, y1);
	while (1)
	{
		mlx_pixel_put(vars()->win->mlx_ptr, \
vars()->win->win_ptr, pos.x, pos.y, pos.color);
		if (pos.x == x1 && pos.y == y1)
			break ;
		vars()->e2 = 2 * vars()->err;
		if (vars()->e2 >= vars()->dy)
		{
			vars()->err += vars()->dy;
			pos.x += vars()->sx;
		}
		if (vars()->e2 <= vars()->dx)
		{
			vars()->err += vars()->dx;
			pos.y += vars()->sy;
		}
	}
}

void	draw_orientation(int size, int color)
{
	int			x1;
	int			y1;
	t_pos		pos;

	(void)size;
	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = color;
	x1 = vars()->player->x + vars()->player->delta_x * 5;
	y1 = vars()->player->y + vars()->player->delta_y * 5;
	draw_line(pos, x1, y1);
}

void	draw_reverse(int size, int color)
{
	int			x1;
	int			y1;
	t_pos		pos;

	(void)size;
	pos.x = vars()->player->x;
	pos.y = vars()->player->y;
	pos.color = color;
	x1 = vars()->player->x - vars()->player->delta_x * 5;
	y1 = vars()->player->y - vars()->player->delta_y * 5;
	draw_line(pos, x1, y1);
}

void	draw_player(t_img img, int size, t_pos position)
{
	t_pos	pos;

	vars()->player->x = position.x;
	vars()->player->y = position.y;
	vars()->player->size = size;
	pos.x = position.x;
	pos.y = position.y;
	pos.color = position.color;
	draw_square(img, size, pos);
	draw_orientation(size, gen_trgb(255, 255, 0, 0));
	draw_reverse(size, gen_trgb(255, 0, 0, 255));
	vars()->player->img = img;
}
