/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:13:23 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/12 11:53:18 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/raycasting.h"

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
	mlx_set_setting(MLX_FULLSCREEN, true);
	data->mlx = mlx_init(data->width, data->height, "Cube3D", true);
	if (!data->mlx)
		ft_error(data, NULL, true);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image || (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0))
		ft_error(data, NULL, true);
	// data->render->pos_x = (double)data->player_pos[0];
	// data->render->pos_y = (double)data->player_pos[1];
	// data->render->dir_x = -1;
	// data->render->dir_y = 0;
	// data->render->camera_plane_x = 0;
	// data->render->camera_plane_y = 0.6;
}

int32_t	main(int ac, char **av)
{
	t_data		data;

	data.gc = gc_new();
	init_cube(ac, av, &data);
	init_structs(&data);
	setup_player(&data);
	// pause();
	init_mlx(&data);
	// Even after the image is being displayed, we can still modify the buffer.
	// raycasting(&data, &vec); // TODO: move (init & gameloop starts here)
	mlx_put_pixel(data.image, 0, 0, 0xFF0000FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!	
	mlx_loop_hook(data.mlx, raycasting, &data);
	// mlx_loop_hook(data.mlx, ft_randomize, &data);
	// mlx_loop_hook(data.mlx, render_player, &data);
	// mlx_loop_hook(data.mlx, render_direction_ray, &data);
	mlx_loop_hook(data.mlx, ft_hook_keys, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	gc_collect(&data.gc);
	return (EXIT_SUCCESS);
}
