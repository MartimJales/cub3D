/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:29:02 by mjales            #+#    #+#             */
/*   Updated: 2024/01/17 16:06:34 by mjales           ###   ########.fr       */
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

	pos.x = 0;
	pos.y = 0;
	mini_cube_size = 16;
	tmp = new_img(vars()->map_width * CUBESIZE, 
vars()->map_height * CUBESIZE, (t_win)window);
	vars()->map_img = tmp;
	tmp = new_img(vars()->map_width * mini_cube_size, 
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


void	print_map(void)
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
				printf("%d", 1);
			else
				printf("%d", vars()->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// int check_grid()
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < vars()->map_height)
// 	{
// 		j = 0;
// 		while (j < vars()->map_width)
// 		{
// 			if (vars()->map[i][j] == 2)
// 			{
// 				if (i > 0 && vars()->map[i - 1][j] == 0)
// 					return (0);
// 				if (i < vars()->map_height - 1 && vars()->map[i + 1][j] == 0)
// 					return (0);
// 				if (j > 0 && vars()->map[i][j - 1] == 0)
// 					return (0);
// 				if (j < vars()->map_width - 1 && vars()->map[i][j + 1] == 0)
// 					return (0);
// 			}
// 			if (vars()->map[i][j] == 0 && (i == vars()->map_height - 1 || j == 0 || j == vars()->map_width - 1 || i == 0))
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int check_borders(int i, int j) {
	return (i == vars()->map_height - 1 || j == 0 || j == vars()->map_width - 1 || i == 0);
}

// Function to check neighboring cells
int check_neighbors(int i, int j) {
	if (i > 0 && vars()->map[i - 1][j] == 0)
		return 0;
	if (i < vars()->map_height - 1 && vars()->map[i + 1][j] == 0)
		return 0;
	if (j > 0 && vars()->map[i][j - 1] == 0)
		return 0;
	if (j < vars()->map_width - 1 && vars()->map[i][j + 1] == 0)
		return 0;
	return 1;
}

// Function to check the entire grid
int check_grid() {
	int i, j;

	i = 0;
	while (i < vars()->map_height) {
		j = 0;
		while (j < vars()->map_width) {
			if (vars()->map[i][j] == 2) {
				if (!check_neighbors(i, j))
					return 0;
			}
			if (vars()->map[i][j] == 0 && check_borders(i, j))
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}


