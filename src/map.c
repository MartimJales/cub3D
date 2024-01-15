/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:29:02 by mjales            #+#    #+#             */
/*   Updated: 2024/01/13 20:30:18 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	map_color(int intensity, int max)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)intensity / max;
	r = (int)(255 * (1 - t) * t * t * t * 6);
	g = (int)(255 * (1 - t) * (1 - t) * t * t * 6);
	b = (int)(255 * (1 - t) * (1 - t) * (1 - t) * t * 6);
	return (gen_trgb(intensity, r, b, g));
}

//aux do create_map
void	map_loop(t_pos pos, int mini_cube_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars()->map_height)
	{
		j = 0;
		while (j < vars()->map_width)
		{
			if (vars()->map[i][j] == 1)
				draw_wall(pos, i, j, mini_cube_size);
			else
				draw_empty(pos, i, j, mini_cube_size);
			j++;
		}
		i++;
	}
}

void	create_map(t_win window)
{
	int			mini_cube_size;
	t_pos		pos;
	t_img		tmp;

	mini_cube_size = 16;
	tmp = new_img(vars()->map_width * CUBESIZE, \
vars()->map_height * CUBESIZE, (t_win)window);
	vars()->map_img = tmp;
	tmp = new_img(vars()->map_width * mini_cube_size, \
vars()->map_height * mini_cube_size, (t_win)window);
	vars()->mini_map = tmp;
	map_loop(pos, mini_cube_size);
}

void	create_squares(t_win window)
{
	t_pos		pos;
	t_img		tmp;

	pos.x = 0;
	pos.y = 0;
	pos.color = gen_trgb(0, 255, 255, 255);
	tmp = new_img(CUBESIZE, CUBESIZE, window);
	vars()->wall = tmp;
	tmp = new_img(CUBESIZE, CUBESIZE, window);
	vars()->floor = tmp;
	draw_square(vars()->wall, CUBESIZE - 1, pos);
	pos.color = gen_trgb(0, 0, 150, 200);
	draw_square(vars()->floor, CUBESIZE - 1, pos);
}
