/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjales <mjales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:04:27 by mjales            #+#    #+#             */
/*   Updated: 2023/12/05 01:34:28 by mjales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

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

int char_to_int(char chr)
{
	return (chr - '0');
}

int check_string(char	*input_str)
{
    int start_index = 0;
    while (input_str[start_index] == ' ')
		start_index++;
    int end_index = strlen(input_str) - 1;
    while (end_index >= 0 && input_str[end_index] == ' ')
		end_index--;
    if (input_str[start_index] == '1' && input_str[end_index] == '1')
        return 0;
    else
        return 1;
}


int validate_string(char	*input_str)
{
	int index = 0;
    while (input_str[index] != '\0')
    {
        char current_char = input_str[index];
        if (!(char_to_int(current_char) == 0 ||  char_to_int(current_char) == 1 ||
              current_char == 'N' || current_char == 'S' ||
              current_char == 'E' || current_char == 'W' ||
              current_char == ' '))
            return 1;
		if (current_char == 'N' || current_char == 'S' ||
			current_char == 'E' || current_char == 'W')
		{
			vars()->player->orientation = current_char;
			vars()->player->startx = index;
			vars()->player->starty = vars()->mapHeight;
			current_char = '0';
		}
		if(current_char == ' ')
			current_char = '0';
		vars()->map[vars()->mapHeight][index] = char_to_int(current_char);
        index++;
    }
    return 0;
}

int get_width(char *input_str) {
    int start_index = 0;
    int end_index = strlen(input_str) - 1;
    while (start_index <= end_index && input_str[start_index] == ' ')
        start_index++;
    while (end_index >= start_index && input_str[end_index] == ' ')
        end_index--;
    int width = 0;
    for (int i = start_index; i <= end_index; i++)
        width++;
    return width;
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
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int check_format(const char *nome_arquivo)
{
    const char *extensao = ft_strrchr(nome_arquivo, '.'); // Encontra a última ocorrência de '.'

    if (extensao != NULL) {
        if (ft_strcmp(extensao, ".cub") == 0) {
            return 1; // Extensão correta
        }
    }

    return 0;// Extensão incorreta;
}

char *get_next_line(int fd)
{
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
}

void parseline(char *line)
{
	if (*line == '\n')
		return ;
	else if (!ft_strncmp(line, "NO", 2)){
		// printf("NO: %s\n", line + 3);
		img_teste(&vars()->NO, line + 3);
	}
	else if (!ft_strncmp(line, "SO", 2))
		img_teste(&vars()->SO, line + 3);
	else if (!ft_strncmp(line, "WE", 2))
		img_teste(&vars()->WE, line + 3);
	else if (!ft_strncmp(line, "EA", 2))
		img_teste(&vars()->EA, line + 3);
	else if (!ft_strncmp(line, "F", 1))
		vars()->fcolor = process_string(line + 2);
	else if (!ft_strncmp(line, "C", 1))
		vars()->ccolor = process_string(line + 2);
	else if (!(validate_string(line)) && !(check_string(line)))
	{
		vars()->mapHeight++;
		if(get_width(line) > vars()->mapWidth)
			vars()->mapWidth = get_width(line);
	}
	else
		printf("Error\nInvalid line\n");
}

void parser(char *filename)
{
	vars()->mapWidth = 0;
	vars()->mapHeight = 0;
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

	// vars()->ceil_img = new_img(vars()->win->width, vars()->win->height / 3, *vars()->win);
	// vars()->floor_img = new_img(vars()->win->width, 2 * vars()->win->height / 3, *vars()->win);
	// fill_image(vars()->ceil_img, vars()->ccolor);
	// fill_image(vars()->floor_img, vars()->fcolor);

	// printf("start_x: %d\n", vars()->player->startx);
	// printf("start_y: %d\n", vars()->player->starty);

	// vars()->player->x = vars()->player->startx * 32;
	// vars()->player->y = vars()->player->starty * 32;

	// printf("x: %f\n", vars()->player->x);
	// printf("y: %f\n", vars()->player->y);

	printf("mapWidth: %d\n", vars()->mapWidth);
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
