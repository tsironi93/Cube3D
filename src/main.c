/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:23 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/16 16:41:15 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

// static void	check_leaks(void)
// {
// 	char	cmd[256];

// 	snprintf(cmd, sizeof(cmd), "leaks %s", getprogname());
// 	system(cmd);
// }

static void	clean_textures(t_data *data)
{
	int	i;

	if (data->textures->north)
		mlx_delete_texture(data->textures->north);
	if (data->textures->south)
		mlx_delete_texture(data->textures->south);
	if (data->textures->west)
		mlx_delete_texture(data->textures->west);
	if (data->textures->east)
		mlx_delete_texture(data->textures->east);
	if (data->textures->ceiling_color)
	{
		i = -1;
		while (data->textures->ceiling_color[++i])
			free(data->textures->ceiling_color[i]);
		free(data->textures->ceiling_color);
	}
	if (data->textures->floor_color)
	{
		i = -1;
		while (data->textures->floor_color[++i])
			free(data->textures->floor_color[i]);
		free(data->textures->floor_color);
	}
}

static void	import_colors(t_data *data)
{
	if (!data->textures->floor_color[0] || !data->textures->floor_color[1]
		|| !data->textures->floor_color[2] || data->textures->floor_color[3]
		|| !data->textures->ceiling_color[0]
		|| !data->textures->ceiling_color[1]
		|| !data->textures->ceiling_color[2]
		|| data->textures->ceiling_color[3])
	{
		clean_textures(data);
		ft_error(data, "Invalid floor or ceiling color", false);
	}
	data->textures->red_floor = ft_atoi(data->textures->floor_color[0]);
	data->textures->green_floor = ft_atoi(data->textures->floor_color[1]);
	data->textures->blue_floor = ft_atoi(data->textures->floor_color[2]);
	data->textures->red_ceiling = ft_atoi(data->textures->ceiling_color[0]);
	data->textures->green_ceiling = ft_atoi(data->textures->ceiling_color[1]);
	data->textures->blue_ceiling = ft_atoi(data->textures->ceiling_color[2]);
	printf(BOLD YELLOW "Colors loaded successfully.\n" RESET);
}

static void	import_textures(t_data *data)
{
	data->textures->north = mlx_load_png(data->textures->north_texture);
	if (!data->textures->north)
	{
		clean_textures(data);
		ft_error(data, "Failed to load north texture", true);
	}
	data->textures->south = mlx_load_png(data->textures->south_texture);
	if (!data->textures->south)
	{
		clean_textures(data);
		ft_error(data, "Failed to load south texture", true);
	}
	data->textures->west = mlx_load_png(data->textures->west_texture);
	if (!data->textures->west)
	{
		clean_textures(data);
		ft_error(data, "Failed to load west texture", true);
	}
	data->textures->east = mlx_load_png(data->textures->east_texture);
	if (!data->textures->east)
	{
		clean_textures(data);
		ft_error(data, "Failed to load east texture", true);
	}
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
	mlx_set_setting(MLX_MAXIMIZED, true);
	data->mlx = mlx_init(data->width, data->height, "Cube3D", true);
	if (!data->mlx)
		ft_error(data, NULL, true);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image || (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0))
		ft_error(data, NULL, true);
	import_textures(data);
	import_colors(data);
}

// atexit(check_leaks);
int32_t	main(int ac, char **av)
{
	t_data	data;

	init_cube(ac, av, &data);
	init_structs(&data);
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
