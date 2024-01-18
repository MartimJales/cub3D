/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:36:46 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 13:07:13 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	handle_exit(int keycode)
{
	if (keycode == ESC_KEY_M || keycode == CROSS)
		exit_program();
}

int	check_borders(int i, int j)
{
	return (i == vars()->map_height - 1 || \
	j == 0 || j == vars()->map_width - 1 || i == 0);
}

// Function to check neighboring cells
int	check_neighbors(int i, int j)
{
	if (i > 0 && vars()->map[i - 1][j] == 0)
		return (0);
	if (i < vars()->map_height - 1 && vars()->map[i + 1][j] == 0)
		return (0);
	if (j > 0 && vars()->map[i][j - 1] == 0)
		return (0);
	if (j < vars()->map_width - 1 && vars()->map[i][j + 1] == 0)
		return (0);
	return (1);
}

// Function to check the entire grid
int	check_grid(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars()->map_height)
	{
		j = 0;
		while (j < vars()->map_width)
		{
			if (vars()->map[i][j] == 2)
			{
				if (!check_neighbors(i, j))
					return (0);
			}
			if (vars()->map[i][j] == 0 && check_borders(i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_images(void)
{
	if (vars()->no.img_ptr && vars()->so.img_ptr && \
	vars()->we.img_ptr && vars()->ea.img_ptr)
		return (1);
	return (0);
}
