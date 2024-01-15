/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:17:54 by mjales            #+#    #+#             */
/*   Updated: 2024/01/13 16:25:27 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void	init_vars(void)
{
	vars()->rx = 0;
	vars()->ry = 0;
	vars()->xo = 0;
	vars()->yo = 0;
	vars()->dist = 0;
	vars()->ra = vars()->player->angle - DR * FOV / 2;
	if (vars()->ra < 0)
		vars()->ra += 2 * PI;
	if (vars()->ra >= 2 * PI)
		vars()->ra -= 2 * PI;
}

t_img	initialize_player_image(void)
{
	t_img	tmp;

	img_teste(&vars()->teste, "pics/colorstone.xpm");
	tmp = new_img(PLAYERSIZE, PLAYERSIZE, *vars()->win);
	return (tmp);
}

t_pos	initialize_player_position(void)
{
	t_pos	pos;

	pos.x = vars()->player->startx * CUBESIZE;
	pos.y = vars()->player->starty * CUBESIZE;
	pos.color = gen_trgb(0, 255, 255, 0);
	return (pos);
}

void	setup_player(void)
{
	if (vars()->player->orientation == 'N')
		vars()->player->angle = -P2;
	else if (vars()->player->orientation == 'S')
		vars()->player->angle = P2;
	else if (vars()->player->orientation == 'E')
		vars()->player->angle = 0;
	else if (vars()->player->orientation == 'W')
		vars()->player->angle = PI;
	vars()->player->delta_x = 5;
	vars()->player->delta_y = 0;
}

void	initialize_game(char *file_path)
{
	t_win		window;
	t_player	player;
	t_img		player_img;

	vars()->player = &player;
	window = new_program(SCREENWIDTH, SCREENHEIGHT, "cub3d");
	vars()->win = &window;
	if (!check_format(file_path))
	{
		printf("Error: extensão do arquivo não é .cub\n");
		exit(1);
	}
	parser(file_path);
	create_squares(window);
	create_map(window);
	player_img = initialize_player_image();
	setup_player();
	draw_player_and_rays(window, player_img);
	handle_hooks_and_put_image(window, player_img);
}