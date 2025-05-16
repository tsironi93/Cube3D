/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:23 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/16 18:47:48 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

static void	texture_and_colors(char *line, t_map_data ref)
{
	if (ref < 4)
		line += 3;
	else
		line++;
	while (ft_isspace(*line))
		line++;
	printf(BOLD YELLOW);
	if (ref == NORTH_TEXTURE)
		printf("NORTH_TEXTURE : %s\n", line);
	if (ref == SOUTH_TEXTURE)
		printf("SOUTH_TEXTURE : %s\n", line);
	if (ref == WEST_TEXTURE)
		printf("WEST_TEXTURE : %s\n", line);
	if (ref == EAST_TEXTURE)
		printf("EAST_TEXTURE : %s\n", line);
	if (ref == FLOOR_COLOR)
		printf("FLOOR_COLOR : %s\n", line);
	if (ref == CEALING_COLOR)
		printf("CEALING_COLOR : %s\n", line);
	printf(RESET);
}

static bool	validate_syntax(int fd)
{
	char	*line;

	while ("MALAKA")
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (*line)
		{
			if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S'
				&& *line != 'E' && *line != 'W' && !ft_isspace(*line) && *line != '\n')
			{
				printf("ERROR in line :%s\n", line);
				return (false);
			}
			line++;
		}
	}
	printf (BOLD YELLOW "Syntax validation succeeded!!\n" RESET);
	return (true);
}

static void	validate_map_file(int fd)
{
	char	*line;

	while ("MALAKA")
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
			continue ;
		else if (!ft_strncmp(line, "NO", 2))
			texture_and_colors(line, NORTH_TEXTURE);
		else if (ft_strnstr(line, "SO", 2))
			texture_and_colors(line, SOUTH_TEXTURE);
		else if (ft_strnstr(line, "WE", 2))
			texture_and_colors(line, WEST_TEXTURE);
		else if (ft_strnstr(line, "EA", 2))
			texture_and_colors(line, EAST_TEXTURE);
		else if (ft_strnstr(line, "F", 1))
			texture_and_colors(line, FLOOR_COLOR);
		else if (ft_strnstr(line, "C", 1))
			texture_and_colors(line, CEALING_COLOR);
		else
			if (!validate_syntax(fd))
				ft_error("Wrong characters found in the map", false);
	}
}

static void	init_cube(int ac, char **av)
{
	char	*map_file;
	int		fd;

	if (ac != 2)
		ft_error("Init error: The only parameter in Cube3D is a map", false);
	if (ft_strcmp(av[1] + (ft_strlen(av[1]) - 4), ".cub"))
		ft_error("Init error: Invalid map file", false);
	map_file = av[1];
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error("Init error: Cant open map or file doesnt exist", false);
	validate_map_file(fd);
	close(fd);
}

static void	init_mlx(t_data *data)
{
	data->width = 2880;
	data->height = 1620;
	mlx_set_setting(MLX_FULLSCREEN, true);
	data->mlx = mlx_init(data->width, data->height, "Cube3D", true);
	if (!data->mlx)
		ft_error(NULL, true);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image || (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0))
		ft_error(NULL, true);
}

int32_t	main(int ac, char **av)
{
	t_data	data;

	init_cube(ac, av);
	init_mlx(&data);
	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(data.image, 0, 0, 0xFF0000FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!	
	mlx_loop_hook(data.mlx, ft_randomize, &data);
	mlx_loop_hook(data.mlx, ft_hook_keys, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
