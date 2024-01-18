/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:04:27 by mjales            #+#    #+#             */
/*   Updated: 2024/01/18 19:10:36 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

char	*read_line(int fd, int *rd)
{
	char	character;
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(100000);
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		*rd = read(fd, &character, 1);
		if (*rd <= 0)
			break ;
		buffer[i++] = character;
		if (character == '\n' || *rd <= 0)
			break ;
	}
	if (i > 0)
		buffer[i - 1] = '\0';
	else
		buffer[i] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	int		rd;
	char	*buffer;

	buffer = read_line(fd, &rd);
	if (rd == -1 || buffer == NULL || (!buffer[0] && rd <= 0))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void	parseline(char *line)
{
	if (*line == '\n')
		return ;
	else if (!ft_strncmp(line, "NO", 2) && ++vars()->tes[0])
		img_teste(&vars()->no, line + 3, line);
	else if (!ft_strncmp(line, "SO", 2) && ++vars()->tes[1])
		img_teste(&vars()->so, line + 3, line);
	else if (!ft_strncmp(line, "WE", 2) && ++vars()->tes[2])
		img_teste(&vars()->we, line + 3, line);
	else if (!ft_strncmp(line, "EA", 2) && ++vars()->tes[3])
		img_teste(&vars()->ea, line + 3, line);
	else if (!ft_strncmp(line, "F", 1) && ++vars()->tes[4])
		vars()->fcolor = process_string(line);
	else if (!ft_strncmp(line, "C", 1) && ++vars()->tes[5])
		vars()->ccolor = process_string(line);
	else if (!(validate_string(line)) && !(check_string(line)))
	{
		if (!vars()->tes[0] || !vars()->tes[1] || !vars()->tes[2] || \
!vars()->tes[3] || !vars()->tes[4] || !vars()->tes[5])
		{
			free(line);
			exit_program(printf("Error: Invalid map\n"));
		}
		if (++vars()->map_height && get_width(line) > vars()->map_width)
			vars()->map_width = get_width(line);
	}
}

void	parser(char *filename)
{
	char	*line;
	int		fd;

	vars()->map_width = 0;
	vars()->map_height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file\n");
		exit_program(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		parseline(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = NULL;
	close(fd);
}

void	fill_image(t_img img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img.w)
	{
		j = 0;
		while (j < img.h)
		{
			put_pixel_img(img, i, j, color);
			j++;
		}
		i++;
	}
}
