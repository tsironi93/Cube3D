/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:16:58 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/19 18:02:54 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void rotate_player(t_data *data, double rotation_speed)
{
	// save old direction
	double old_dir_x = data->vec->dir_x;
	double old_plane_x = data->vec->plane_x;
	
	// rotate direction vector
	data->vec->dir_x = data->vec->dir_x * cos(rotation_speed) - data->vec->dir_y * sin(rotation_speed);
	data->vec->dir_y = old_dir_x * sin(rotation_speed) + data->vec->dir_y * cos(rotation_speed);
	
	// rotate camera plane
	data->vec->plane_x = data->vec->plane_x * cos(rotation_speed) - data->vec->plane_y * sin(rotation_speed);
	data->vec->plane_y = old_plane_x * sin(rotation_speed) + data->vec->plane_y * cos(rotation_speed);
}

void	ft_hook_keys(void *param)
{
	t_data	*data;
	float	old_position_x;
	float	old_position_y;
	float	new_position_x;
	float	new_position_y;
	float	example_position_x;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) // forward
	{
		example_position_x = 9.32;
		printf("example_position_x number = %f\n", example_position_x);
		printf("example_position_x number INT = %d\n", (int)round(example_position_x));
		example_position_x = 9.72;
		printf("example_position_x number = %f\n", example_position_x);
		printf("example_position_x number INT = %d\n", (int)round(example_position_x));
		
		// inside_of_walls(data->player->player_pos_x, data->player->player_pos_y, data);
		old_position_x = data->player->player_pos_x;
		old_position_y = data->player->player_pos_y;
		// moving and getting new position
		new_position_x = old_position_x + data->vec->dir_x * 0.05;
		new_position_y = old_position_y + data->vec->dir_y * 0.05;
		// if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(old_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(new_position_x)][(int)round(old_position_y)] == '1') \
		// || (data->map[(int)new_position_x][(int)new_position_y] == '1') || (data->map[(int)old_position_x][(int)new_position_y] == '1') || (data->map[(int)new_position_x][(int)old_position_y] == '1'))
		if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)new_position_x][(int)new_position_y] == '1'))
		{
			printf("cant move, wall detected\n");
		}
		else
		{
			data->player->player_pos_x += data->vec->dir_x * 0.05; // move speed (how far players moves per update)
			data->player->player_pos_y += data->vec->dir_y * 0.05;
		}
		printf("Player pos NEW: x=%f, y=%f\n", data->player->player_pos_x, data->player->player_pos_y);
		printf("Grid pos: x=%d, y=%d\n", data->vec->grid_map_x, data->vec->grid_map_y);
		printf("map xy = %c\n", data->map[(int)(data->player->player_pos_x)][(int)(data->player->player_pos_y)]);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) // backward
	{
		old_position_x = data->player->player_pos_x;
		old_position_y = data->player->player_pos_y;
		// moving and getting new position
		new_position_x = old_position_x - data->vec->dir_x * 0.05;
		new_position_y = old_position_y - data->vec->dir_y * 0.05;
		// if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(old_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(new_position_x)][(int)round(old_position_y)] == '1') \
		// || (data->map[(int)new_position_x][(int)new_position_y] == '1') || (data->map[(int)old_position_x][(int)new_position_y] == '1') || (data->map[(int)new_position_x][(int)old_position_y] == '1'))
		if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)new_position_x][(int)new_position_y] == '1'))		
		{
			printf("cant move, wall detected\n");
		}
		else
		{
			data->player->player_pos_x -= data->vec->dir_x * 0.05;
			data->player->player_pos_y -= data->vec->dir_y * 0.05;
		}
		printf("Player pos NEW: x=%f, y=%f\n", data->player->player_pos_x, data->player->player_pos_y);
		printf("Grid pos: x=%d, y=%d\n", data->vec->grid_map_x, data->vec->grid_map_y);
		printf("map xy = %c\n", data->map[(int)(data->player->player_pos_x)][(int)(data->player->player_pos_y)]);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) // strafe left 
	{
		old_position_x = data->player->player_pos_x;
		old_position_y = data->player->player_pos_y;
		// moving and getting new position
		new_position_x = old_position_x - data->vec->plane_x * 0.05;
		new_position_y = old_position_y - data->vec->plane_y * 0.05;
		// if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(old_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(new_position_x)][(int)round(old_position_y)] == '1') \
		// || (data->map[(int)new_position_x][(int)new_position_y] == '1') || (data->map[(int)old_position_x][(int)new_position_y] == '1') || (data->map[(int)new_position_x][(int)old_position_y] == '1'))
		if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)new_position_x][(int)new_position_y] == '1'))	
		{
			printf("cant move, wall detected\n");
		}
		else
		{
			data->player->player_pos_x -= data->vec->plane_x * 0.05;
			data->player->player_pos_y -= data->vec->plane_y * 0.05;
		}
		printf("Player pos NEW: x=%f, y=%f\n", data->player->player_pos_x, data->player->player_pos_y);
		printf("Grid pos: x=%d, y=%d\n", data->vec->grid_map_x, data->vec->grid_map_y);
		printf("map xy = %c\n", data->map[(int)(data->player->player_pos_x)][(int)(data->player->player_pos_y)]);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) // strafe right
	{
		old_position_x = data->player->player_pos_x;
		old_position_y = data->player->player_pos_y;
		// moving and getting new position
		new_position_x = old_position_x + data->vec->plane_x * 0.05;
		new_position_y = old_position_y + data->vec->plane_y * 0.05;
		// if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(old_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)round(new_position_x)][(int)round(old_position_y)] == '1') \
		// || (data->map[(int)new_position_x][(int)new_position_y] == '1') || (data->map[(int)old_position_x][(int)new_position_y] == '1') || (data->map[(int)new_position_x][(int)old_position_y] == '1'))
		if ((data->map[(int)round(new_position_x)][(int)round(new_position_y)] == '1') || (data->map[(int)new_position_x][(int)new_position_y] == '1'))	
		{
			printf("cant move, wall detected\n");
		}
		else
		{
			data->player->player_pos_x += data->vec->plane_x * 0.05;
			data->player->player_pos_y += data->vec->plane_y * 0.05;
		}
		printf("Player pos NEW: x=%f, y=%f\n", data->player->player_pos_x, data->player->player_pos_y);
		printf("Grid pos: x=%d, y=%d\n", data->vec->grid_map_x, data->vec->grid_map_y);
		printf("map xy = %c\n", data->map[(int)(data->player->player_pos_x)][(int)(data->player->player_pos_y)]);
	}
	
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) // rotate right
		rotate_player(data, 0.05); 
	
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) // rotate left
		rotate_player(data, -0.05);
}



// rotation [OLD]
// if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) // rotates left
// {
// 	data->player->player_angle -= 0.1;
// 	if (data->player->player_angle < 0)
// 		data->player->player_angle += 2 * PI;
// 	data->player->player_delta_x = cos(data->player->player_angle);
// 	data->player->player_delta_y = sin(data->player->player_angle);
// }
// if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) // rotates right
// {
// 	data->player->player_angle += 0.1;
// 	if (data->player->player_angle > 2 * PI)
// 		data->player->player_angle -= 2 * PI;
// 	data->player->player_delta_x = cos(data->player->player_angle);
// 	data->player->player_delta_y = sin(data->player->player_angle);
// }
