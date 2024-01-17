/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:13:18 by mjales            #+#    #+#             */
/*   Updated: 2024/01/10 12:30:11 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	draw_wall(t_pos pos, int i, int j, int mini_cube_size)
{
	pos.x = j * mini_cube_size;
	pos.y = i * mini_cube_size;
	pos.color = gen_trgb(0, 255, 255, 255);
	draw_square(vars()->mini_map, mini_cube_size - 1, pos);
	pos.x = j * CUBESIZE;
	pos.y = i * CUBESIZE;
	draw_square(vars()->map_img, CUBESIZE - 1, pos);
}

void	draw_empty(t_pos pos, int i, int j, int mini_cube_size)
{
	pos.x = j * mini_cube_size;
	pos.y = i * mini_cube_size;
	pos.color = gen_trgb(0, 0, 150, 200);
	draw_square(vars()->mini_map, mini_cube_size - 1, pos);
	pos.x = j * CUBESIZE;
	pos.y = i * CUBESIZE;
	draw_square(vars()->map_img, CUBESIZE - 1, pos);
}

void	draw_rectagle(int width, int height, t_pos pos)
{
	int	i;
	int	j;

	i = pos.x;
	while (i < pos.x + width)
	{
		j = pos.y;
		while (j < pos.y + height)
		{
			put_pixel_img(vars()->canvas, i, j, pos.color);
			j++;
		}
		i++;
	}
}
