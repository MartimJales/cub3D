/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psm <psm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:42:08 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 03:01:12 by psm              ###   ########.fr       */
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
		vars()->yo = -CUBESIZE;
		vars()->xo = -vars()->yo * vars()->atan;
	}
	if (ra < PI)
	{
		vars()->ry = (((int)vars()->player->y >> 6) << 6) + CUBESIZE;
		vars()->rx = (vars()->player->y - vars()->ry) * \
vars()->atan + vars()->player->x;
		vars()->yo = CUBESIZE;
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
		vars()->xo = -CUBESIZE;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
	if (ra < P2 || ra > P3)
	{
		vars()->rx = (((int)vars()->player->x >> 6) << 6) + CUBESIZE;
		vars()->ry = (vars()->player->x - vars()->rx) * \
vars()->ntan + vars()->player->y;
		vars()->xo = CUBESIZE;
		vars()->yo = -vars()->xo * vars()->ntan;
	}
}

void	up_or_down(double ra)
{
	if (ra == 0 || ra == PI)
	{
		vars()->rx = vars()->player->x;
		vars()->ry = vars()->player->y;
		vars()->dof = 8;
	}
}
