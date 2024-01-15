/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:42:08 by mjales            #+#    #+#             */
/*   Updated: 2024/01/10 12:47:07 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	look_up_or_down(double ra)
{
	if (ra > PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) - 0.0001;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = -64;
		vars()->xo = -vars()->yo * vars()->atan;
	}
	if (ra < PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) + 64;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = 64;
		vars()->xo = -vars()->yo * vars()->atan;
	}
}

void	look_left_or_right(double ra)
{
	if (ra == 0 || ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
}

void	left_or_right(double ra)
{
	if (ra > P2 && ra < P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) - 0.0001;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = -64;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
	if (ra < P2 || ra > P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) + 64;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = 64;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
}

//aux do vertical_check
void	up_or_down(double ra)
{
	if (ra == 0 || ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
}
