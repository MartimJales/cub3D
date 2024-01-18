/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:17:54 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 14:41:02 by dcordovi         ###   ########.fr       */
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
	vars()->ra = vars()->player->angle - (vars()->dr * SCREENWIDTH / 2);
	if (vars()->ra < 0)
		vars()->ra += 2 * PI;
	if (vars()->ra >= 2 * PI)
		vars()->ra -= 2 * PI;
}

t_pos	initialize_player_position(void)
{
	t_pos	pos;

	pos.x = vars()->player->startx * CUBESIZE;
	pos.y = vars()->player->starty * CUBESIZE;
	pos.color = gen_trgb(0, 255, 255, 0);
	vars()->player->x = pos.x;
	vars()->player->y = pos.y;
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
	vars()->player->delta_x = cos(vars()->player->angle) * 5;
	vars()->player->delta_y = sin(vars()->player->angle) * 5;
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
		exit(printf("Error: extensão do arquivo não é .cub\n") != 0);
	parser(file_path);
	if (!check_images())
		exit(printf("Error: wrong texture paths\n") != 0);
	if (!check_grid() || !vars()->player->orientation)
		exit(printf("Erro: mapa inválido\n") != 0);
	create_squares(window);
	create_map(window);
	player_img = new_img(SCREENWIDTH, SCREENHEIGHT, window);
	vars()->canvas = player_img;
	setup_player();
	draw_player_and_rays(window);
	handle_hooks_and_put_image(window, player_img);
}
