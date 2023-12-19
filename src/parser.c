/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:04:27 by mjales            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/19 15:55:06 by mjales           ###   ########.fr       */
=======
/*   Updated: 2023/11/28 12:42:30 by mjales           ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

<<<<<<< HEAD
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}


int	char_to_int(char chr)
{
	return (chr - '0');
}

int	check_string(char	*input_str)
{
	int	start_index;
	int	end_index;

	end_index = strlen(input_str) - 1;
	start_index = 0;
	while (input_str[start_index] == ' ')
		start_index++;

	while (end_index >= 0 && input_str[end_index] == ' ')
		end_index--;
	if (input_str[start_index] == '1' && input_str[end_index] == '1')
		return (0);
	else
		return (1);
}


int	validate_string(char	*input_str)
{
	int		index;
	char	current_char;

	index = 0;
	while (input_str[index] != '\0')
	{
		current_char = input_str[index];
		if (!(char_to_int(current_char) == 0 || \
char_to_int(current_char) == 1 || \
current_char == 'N' || current_char == 'S' || \
current_char == 'E' || current_char == 'W' || \
current_char == ' '))
			return (1);
		if (current_char == 'N' || current_char == 'S' || \
			current_char == 'E' || current_char == 'W')
		{
			vars()->player->orientation = current_char;
			vars()->player->startx = index;
			vars()->player->starty = vars()->map_height;
			current_char = '0';
		}
		if (current_char == ' ')
			current_char = '0';
		vars()->map[vars()->map_height][index] = char_to_int(current_char);
		index++;
	}
	return (0);
}

int	get_width(char *input_str)
{
	int	start_index;
	int	end_index;
	int	width;
	int	i;

	start_index = 0;
	end_index = strlen(input_str) - 1;
	while (start_index <= end_index && input_str[start_index] == ' ')
		start_index++;
	while (end_index >= start_index && input_str[end_index] == ' ')
		end_index--;
	width = 0;
	i = start_index;
	while (i <= end_index)
	{
		width++;
		i++;
	}
	return (width);
}



int	convert_to_int(const char *start, const char *end)
{
	int		length;
	char	number_str[4];

	length = end - start;

	if (length >= 4 || length <= 0)
	{
		printf("Erro: Segmento inválido.\n");
		return (-1);
	}

	ft_strncpy(number_str, start, length);
	number_str[length] = '\0';

	return (atoi(number_str));
}

int	process_string(const char *str)
{
	int			red;
	int			green;
	int			blue;
	int 		segment_count;
	const char	*segment_start;
	const char	*current_char;

	red = 0;
	green = 0;
	blue = 0;
	segment_start = str;
	current_char = str;
	segment_count = 0;

	while (*current_char != '\0') {
		if (*current_char == ',' || *(current_char + 1) == '\0') {
			const char *segment_end;
			if (*current_char == ',') {
				segment_end = current_char;
			} else {
				segment_end = current_char + 1;
			}

			int value = convert_to_int(segment_start, segment_end);
			if (value == -1)
				return (0);
			if (segment_count == 0) red = value;
			else if (segment_count == 1) green = value;
			else if (segment_count == 2) blue = value;

			segment_start = current_char + 1;
			segment_count++;
		}
		current_char++;
	}

	if (segment_count != 3)
	{
		printf("Erro: Número incorreto de segmentos.\n");
		return (0);
	}
	printf("red: %d\n", red);
	printf("green: %d\n", green);
	printf("blue: %d\n", blue);
	return (gen_trgb(255, red, green, blue));
}


//auxiliares parsing
char* ft_strrchr(const char *str, int c)
{
	char *ultima_ocorrencia = NULL;

	while (*str != '\0') {
		if (*str == c) {
			ultima_ocorrencia = (char*)str;
		}
		str++;
	}

	return ultima_ocorrencia;
=======
char *ft_strncpy(char *dest, const char *src, size_t n) {
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for ( ; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}


int convert_to_int(const char *start, const char *end) {
    int length = end - start;
    char number_str[4]; // Suficiente para armazenar um número até 255 e o caractere nulo

    if (length >= 4 || length <= 0) {
        printf("Erro: Segmento inválido.\n");
        return -1;
    }

    ft_strncpy(number_str, start, length);
    number_str[length] = '\0'; // Garantindo o terminador nulo

    return atoi(number_str);
}

int process_string(const char *str) {
    int red, green, blue;
	red=0;
	green=0;
	blue=0;
    const char *segment_start = str;
    const char *current_char = str;
    int segment_count = 0;

    while (*current_char != '\0') {
        if (*current_char == ',' || *(current_char + 1) == '\0') {
            const char *segment_end = (*current_char == ',') ? current_char : current_char + 1;
            int value = convert_to_int(segment_start, segment_end);
            if (value == -1) {
                return 0;
            }

            if (segment_count == 0) red = value;
            else if (segment_count == 1) green = value;
            else if (segment_count == 2) blue = value;

            segment_start = current_char + 1;
            segment_count++;
        }
        current_char++;
    }

    if (segment_count != 3) {
        printf("Erro: Número incorreto de segmentos.\n");
        return 0;
    }
	printf("red: %d\n", red);
	printf("green: %d\n", green);
	printf("blue: %d\n", blue);
    return gen_trgb(255, red, green, blue);
}

//auxiliares parsing
char* ft_strrchr(const char *str, int c)
{
    char *ultima_ocorrencia = NULL;

    while (*str != '\0') {
        if (*str == c) {
            ultima_ocorrencia = (char*)str;
        }
        str++;
    }

    return ultima_ocorrencia;
>>>>>>> origin/main
}

int ft_strcmp(const char *s1, const char *s2)
{
<<<<<<< HEAD
	while (*s1 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}

	return *(unsigned char *)s1 - *(unsigned char *)s2;
=======
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
>>>>>>> origin/main
}

int check_format(const char *nome_arquivo)
{
<<<<<<< HEAD
	const char *extensao = ft_strrchr(nome_arquivo, '.'); // Encontra a última ocorrência de '.'

	if (extensao != NULL) {
		if (ft_strcmp(extensao, ".cub") == 0) {
			return 1; // Extensão correta
		}
	}

	return 0;// Extensão incorreta;
=======
    const char *extensao = ft_strrchr(nome_arquivo, '.'); // Encontra a última ocorrência de '.'

    if (extensao != NULL) {
        if (ft_strcmp(extensao, ".cub") == 0) {
            return 1; // Extensão correta
        }
    }

    return 0;// Extensão incorreta;
>>>>>>> origin/main
}

char *get_next_line(int fd)
{
<<<<<<< HEAD
	int i = 0;
	int rd = 0;
	char character;

	char *buffer = malloc(100000); // check before the current 1 and then malloc
	while ((rd = read(fd, &character, 1)) > 0)
	{
		buffer[i++] = character;
		if (character == '\n')
			break;
	}
	buffer[i-1] = '\0';
	if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
		return (free(buffer), NULL);
	return (buffer);
=======
    int i = 0;
    int rd = 0;
    char character;

    char *buffer = malloc(100000); // check before the current 1 and then malloc
    while ((rd = read(fd, &character, 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    buffer[i-1] = '\0';
    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);
    return (buffer);
>>>>>>> origin/main
}

void parseline(char *line)
{
	if (*line == '\n')
		return ;
	else if (!ft_strncmp(line, "NO", 2)){
		// printf("NO: %s\n", line + 3);
<<<<<<< HEAD
		img_teste(&vars()->no, line + 3);
	}
	else if (!ft_strncmp(line, "SO", 2))
		img_teste(&vars()->so, line + 3);
	else if (!ft_strncmp(line, "WE", 2))
		img_teste(&vars()->we, line + 3);
	else if (!ft_strncmp(line, "EA", 2))
		img_teste(&vars()->ea, line + 3);
=======
		img_teste(&vars()->NO, line + 3);
	}
	else if (!ft_strncmp(line, "SO", 2))
		img_teste(&vars()->SO, line + 3);
	else if (!ft_strncmp(line, "WE", 2))
		img_teste(&vars()->WE, line + 3);
	else if (!ft_strncmp(line, "EA", 2))
		img_teste(&vars()->EA, line + 3);
>>>>>>> origin/main
	else if (!ft_strncmp(line, "F", 1))
		vars()->fcolor = process_string(line + 2);
	else if (!ft_strncmp(line, "C", 1))
		vars()->ccolor = process_string(line + 2);
<<<<<<< HEAD
	else if (!(validate_string(line)) && !(check_string(line)))
	{
		vars()->map_height++;
		if(get_width(line) > vars()->map_width)
			vars()->map_width = get_width(line);
	}
=======
>>>>>>> origin/main
	else
		printf("Error\nInvalid line\n");
}

void parser(char *filename)
{
<<<<<<< HEAD
	vars()->map_width = 0;
	vars()->map_height = 0;
=======
>>>>>>> origin/main
	// Open filename
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file\n");
		exit(1);
	}
	// Read file
	char *line = get_next_line(fd);
	while (line)
	{
		// printf("%s", line);
		printf("_________\n");
		parseline(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	// Close filename
	close(fd);

<<<<<<< HEAD
	vars()->ceil_img = new_img(SCREENWIDTH, (int)SCREENHEIGHT / 3, *vars()->win);
	vars()->floor_img = new_img(SCREENWIDTH, (int)2 * SCREENHEIGHT / 3, *vars()->win);
	fill_image(vars()->ceil_img, vars()->ccolor);
	fill_image(vars()->floor_img, vars()->fcolor);

	// printf("start_x: %d\n", vars()->player->startx);
	// printf("start_y: %d\n", vars()->player->starty);

	// vars()->player->x = vars()->player->startx * 32;
	// vars()->player->y = vars()->player->starty * 32;

	// printf("x: %f\n", vars()->player->x);
	// printf("y: %f\n", vars()->player->y);

	printf("map_width: %d\n", vars()->map_width);
}

void	fill_image(t_img img, int color)
{
	int i = 0;
	while (i < img.w)
	{
		int j = 0;
		while (j < img.h)
		{
			put_pixel_img(img, i, j, color);
			j++;
		}
		i++;
	}
}
=======
	vars()->ceil_img = new_img(vars()->win->width, vars()->win->height / 3, *vars()->win);
	vars()->floor_img = new_img(vars()->win->width, 2 * vars()->win->height / 3, *vars()->win);
	fill_image(vars()->ceil_img, vars()->ccolor);
	fill_image(vars()->floor_img, vars()->fcolor);

	vars()->mapWidth = 8;
	vars()->mapHeight = 8;
}

void  fill_image(t_img img, int color)
{
	for (int i = 0; i < img.w; i++)
	{
		for (int j = 0; j < img.h; j++)
		{
			put_pixel_img(img, i, j, color);
		}
	}
}

// void draw_square(t_img img,int size, int color)
// {
// 	for (int i = 0; i < size; i++)
// 	{
// 		for (int j = 0; j < size; j++)
// 		{
// 			put_pixel_img(img, i, j, color);
// 		}
// 	}
// }
>>>>>>> origin/main
