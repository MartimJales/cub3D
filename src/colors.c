/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:22:51 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 15:15:44 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int	gen_trgb(int opacity, int red, int green, int blue)
{
	if (opacity > 255 || red > 255 || green > 255 || blue > 255)
		return (0);
	return (opacity << 24 | red << 16 | green << 8 | blue);
}

void	init_colors(const char *str)
{
	vars()->red = 0;
	vars()->green = 0;
	vars()->blue = 0;
	vars()->segment_start = str;
	vars()->segment_count = 0;
}

void	wall_color(void)
{
	int	color;

	color = gen_trgb(255, (int)0, 0, 0);
	if (vars()->distv <= vars()->disth)
	{
		vars()->rx = vars()->vx;
		vars()->ry = vars()->vy;
		vars()->dist = vars()->distv;
		color = gen_trgb(0, (int)255, 0, 0);
	}
	if (vars()->distv > vars()->disth)
	{
		vars()->rx = vars()->hx;
		vars()->ry = vars()->hy;
		vars()->dist = vars()->disth;
		color = gen_trgb(0, (int)100, 0, 0);
	}
	vars()->color_wall = color;
}
