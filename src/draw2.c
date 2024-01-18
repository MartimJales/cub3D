/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:13:18 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 16:23:51 by dcordovi         ###   ########.fr       */
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

void	draw_rays_2d(t_win window)
{
	double	ra;

	init_vars();
	vars()->r = 0;
	ra = vars()->ra;
	while (vars()->r < SCREENWIDTH)
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

void	draw_player_and_rays(t_win window)
{
	initialize_player_position();
	draw_rays_2d(window);
}
