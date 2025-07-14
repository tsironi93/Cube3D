/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:23 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/14 18:32:51 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	check_leaks(void)
{
	char	cmd[256];

	snprintf(cmd, sizeof(cmd), "leaks %s", getprogname());
	system(cmd);
}

static void	clean_textures(t_data *data)
{
	int	i;

	mlx_delete_texture(data->textures->north);
	mlx_delete_texture(data->textures->south);
	mlx_delete_texture(data->textures->west);
	mlx_delete_texture(data->textures->east);
	i = -1;
	while (data->textures->ceiling_color[++i])
		free(data->textures->ceiling_color[i]);
	free(data->textures->ceiling_color);
	i = -1;
	while (data->textures->floor_color[++i])
		free(data->textures->floor_color[i]);
	free(data->textures->floor_color);
}

static void	import_textures(t_data *data)
{
	data->textures->north = mlx_load_png(data->textures->north_texture);
	if (!data->textures->north)
		ft_error(data, "Failed to load north texture", true);
	data->textures->south = mlx_load_png(data->textures->south_texture);
	if (!data->textures->south)
		ft_error(data, "Failed to load south texture", true);
	data->textures->west = mlx_load_png(data->textures->west_texture);
	if (!data->textures->west)
		ft_error(data, "Failed to load west texture", true);
	data->textures->east = mlx_load_png(data->textures->east_texture);
	if (!data->textures->east)
		ft_error(data, "Failed to load east texture", true);
	if (!data->textures->floor_color[0] || !data->textures->floor_color[1]
		|| !data->textures->floor_color[2] || !data->textures->ceiling_color[0]
		|| !data->textures->ceiling_color[1]
		|| !data->textures->ceiling_color[2])
	{
		clean_textures(data);
		ft_error(data, "Invalid floor or ceiling color", true);
	}
	data->textures->red_floor = ft_atoi(data->textures->floor_color[0]);
	data->textures->green_floor = ft_atoi(data->textures->floor_color[1]);
	data->textures->blue_floor = ft_atoi(data->textures->floor_color[2]);
	data->textures->red_ceiling = ft_atoi(data->textures->ceiling_color[0]);
	data->textures->green_ceiling = ft_atoi(data->textures->ceiling_color[1]);
	data->textures->blue_ceiling = ft_atoi(data->textures->ceiling_color[2]);
	printf(BOLD YELLOW "Loading textures...\n" RESET);
	printf(BOLD YELLOW "North texture: %s\n" RESET, data->textures->north_texture);
	printf(BOLD YELLOW "South texture: %s\n" RESET, data->textures->south_texture);
	printf(BOLD YELLOW "West texture: %s\n" RESET, data->textures->west_texture);
	printf(BOLD YELLOW "East texture: %s\n" RESET, data->textures->east_texture);
	printf(BOLD YELLOW "Floor color: %s, %s, %s\n" RESET,
		data->textures->floor_color[0], data->textures->floor_color[1],
		data->textures->floor_color[2]);
	printf(BOLD YELLOW "Ceiling color: %d, %d, %d\n" RESET,
		data->textures->red_ceiling, data->textures->green_ceiling,
		data->textures->blue_ceiling);
	printf(BOLD YELLOW "Textures loaded successfully.\n" RESET);
}

static void	init_mlx(t_data *data)
{
	t_player	*player;

	data->width = 2880;
	data->height = 1620;
	player = gc_malloc(&data->gc, sizeof(t_player));
	data->player = player;
	player->player_pos_x = (float)data->player_pos[0];
	player->player_pos_y = (float)data->player_pos[1];
	data->player->player_angle = PI / 2;
	data->player->player_delta_x = cos(data->player->player_angle);
	data->player->player_delta_y = sin(data->player->player_angle);
	mlx_set_setting(MLX_MAXIMIZED, true);
	data->mlx = mlx_init(data->width, data->height, "Cube3D", true);
	if (!data->mlx)
		ft_error(data, NULL, true);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image || (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0))
		ft_error(data, NULL, true);
	import_textures(data);
}

int32_t	main(int ac, char **av)
{
	t_data	data;

	init_cube(ac, av, &data);
	init_structs(&data);
	atexit(check_leaks);
	init_mlx(&data);
	setup_player(&data, data.vec);
	mlx_loop_hook(data.mlx, raycasting, &data);
	mlx_loop_hook(data.mlx, render_minimap, &data);
	mlx_loop_hook(data.mlx, ft_hook_keys, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.image);
	clean_textures(&data);
	mlx_terminate(data.mlx);
	gc_collect(&data.gc);
	return (EXIT_SUCCESS);
}
