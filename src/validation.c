/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:59:12 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/12 13:27:09 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	texture_and_colors(t_data *data, char *line, t_map_data ref)
{
	while (ft_isspace(*line))
		line++;
	line = ft_strtrim(line, "\n");
	if (ref == NORTH_TEXTURE)
		data->textures->north_texture = gc_strdup(&data->gc, line);
	else if (ref == SOUTH_TEXTURE)
		data->textures->south_texture = gc_strdup(&data->gc, line);
	else if (ref == WEST_TEXTURE)
		data->textures->west_texture = gc_strdup(&data->gc, line);
	else if (ref == EAST_TEXTURE)
		data->textures->east_texture = gc_strdup(&data->gc, line);
	else if (ref == FLOOR_COLOR)
		data->textures->floor_color = ft_split(line, ',');
	else if (ref == CEILING_COLOR)
		data->textures->ceiling_color = ft_split(line, ',');
}

static bool	validate_syntax(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
				return (printf(BOLD YELLOW "\n Error found in :%s line %d\n",
						map[i], i), false);
		}
	}
	printf (BOLD YELLOW "Syntax validation succeeded!!\n" RESET);
	return (true);
}

// void	alloc_map(int *i, t_data *data, char *map_buffer, size_t max_len)
// {
// 	int		j;
// 	char	**map;
//
// 	data->map = map;
// 	j = -1;
// 	*map = gc_malloc(&data->gc, (*i + 1) * sizeof(char *));
// 	while (++j < *i)
// 	{
// 		(*map)[j] = gc_malloc(&data->gc, max_len + 1);
// 		ft_memset((*map)[j], ' ', max_len);
// 		ft_memcpy((*map)[j], map_buffer[j], ft_strlen(map_buffer[j]));
// 		(*map)[j][max_len] = '\0';
// 	}
// 	(*map)[j] = NULL;
// 	data->map_height = *i;
// 	*i = -1;
// }
//
// static void	fetch_map(t_data *data, char *line, char ***map)
// {
// 	static char		*map_buffer[1024];
// 	static int		i;
// 	int				j;
// 	char			*new_line;
// 	static size_t	max_len;
//
// 	j = -1;
// 	if ((!line && i == 0) || i < 0)
// 		return ;
// 	if (!line && i != 0)
// 	{
// 		alloc_map(&i, data, map_buffer, max_len);
// 		*map = gc_malloc(&data->gc, (i + 1) * sizeof(char *));
// 		while (++j < i)
// 		{
// 			(*map)[j] = gc_malloc(&data->gc, max_len + 1);
// 			ft_memset((*map)[j], ' ', max_len);
// 			ft_memcpy((*map)[j], map_buffer[j], ft_strlen(map_buffer[j]));
// 			(*map)[j][max_len] = '\0';
// 		}
// 		(*map)[j] = NULL;
// 		data->map_height = i;
// 		i = -1;
// 	}
// 	else
// 	{
// 		new_line = ft_strtrim(line, "\n");
// 		if (max_len < ft_strlen(new_line))
// 			max_len = ft_strlen(new_line);
// 		map_buffer[i++] = new_line;
// 	}
// }

static void	store_line(char *line, char *map_buffer[], int *i, size_t *max_len)
{
	char	*new_line;

	new_line = ft_strtrim(line, "\n");
	if (*max_len < ft_strlen(new_line))
		*max_len = ft_strlen(new_line);
	map_buffer[(*i)++] = new_line;
}

static void	finalize_map(t_data *data, char ***map, char *map_buffer[], int *i, size_t max_len)
{
	int	j;

	j = -1;
	*map = gc_malloc(&data->gc, (*i + 1) * sizeof(char *));
	while (++j < *i)
	{
		(*map)[j] = gc_malloc(&data->gc, max_len + 1);
		ft_memset((*map)[j], ' ', max_len);
		ft_memcpy((*map)[j], map_buffer[j], ft_strlen(map_buffer[j]));
		(*map)[j][max_len] = '\0';
	}
	(*map)[j] = NULL;
	data->map_height = *i;
	*i = -1;
}

static void	fetch_map(t_data *data, char *line, char ***map)
{
	static char		*map_buffer[1024];
	static int		i;
	static size_t	max_len;

	if ((!line && i == 0) || i < 0)
		return ;
	if (!line && i != 0)
		finalize_map(data, map, map_buffer, &i, max_len);
	else
		store_line(line, map_buffer, &i, &max_len);
}

static void	validate_file(int fd, t_data *data)
{
	char	*line;

	while (MALAKA)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strcmp(line, "\n"))
			continue ;
		if (ft_strnstr(line, "NO", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "NO",
					ft_strlen(line)) + 2, NORTH_TEXTURE);
		else if (ft_strnstr(line, "SO", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "SO",
					ft_strlen(line)) + 2, SOUTH_TEXTURE);
		else if (ft_strnstr(line, "WE", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "WE",
					ft_strlen(line)) + 2, WEST_TEXTURE);
		else if (ft_strnstr(line, "EA", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "EA",
					ft_strlen(line)) + 2, EAST_TEXTURE);
		else if (ft_strnstr(line, "F", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "F",
					ft_strlen(line)) + 1, FLOOR_COLOR);
		else if (ft_strnstr(line, "C", ft_strlen(line)))
			texture_and_colors(data, ft_strnstr(line, "C",
					ft_strlen(line)) + 1, CEILING_COLOR);
		else
			fetch_map(data, line, &data->map);
	}
}

void	init_cube(int ac, char **av, t_data *data)
{
	int		fd;

	data->gc = gc_new();
	if (ac != 2)
		ft_error(data, "Init error: The only parameter in Cube3D is a map",
			false);
	if (ft_strcmp(av[1] + (ft_strlen(av[1]) - 4), ".cub"))
		ft_error(data, "Init error: Invalid map file", false);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error(data, "Init error: Cant open map or file doesnt exist", false);
	data->textures = gc_malloc(&data->gc, sizeof(t_textures));
	ft_bzero(data->textures, sizeof(t_textures));
	validate_file(fd, data);
	if (data->textures->north_texture == NULL
		|| data->textures->south_texture == NULL
		|| data->textures->east_texture == NULL
		|| data->textures->floor_color == NULL
		|| data->textures->ceiling_color == NULL)
		ft_error(data, "Init error: Missing textures or colors", false);
	fetch_map(data, NULL, &data->map);
	if (!validate_syntax(data->map))
		ft_error(data, "Wrong characters found in the map", false);
	find_player_pos(data, data->map);
	flood_check(data, clone_map(data, data->map), data->player_pos[0],
		data->player_pos[1]);
	close(fd);
}
