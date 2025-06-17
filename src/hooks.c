/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:16:58 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/17 20:16:02 by pdrettas         ###   ########.fr       */
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

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) // forward
	{
		data->player->player_pos_x += data->vec->dir_x * 0.05; // move speed (how far players moves per update)
    	data->player->player_pos_y += data->vec->dir_y * 0.05;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) // backward
	{
		data->player->player_pos_x -= data->vec->dir_x * 0.05; 
    	data->player->player_pos_y -= data->vec->dir_y * 0.05;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) // strafe left 
	{
		data->player->player_pos_x -= data->vec->plane_x * 0.05;
		data->player->player_pos_y -= data->vec->plane_y * 0.05;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) // strafe right
	{
		data->player->player_pos_x += data->vec->plane_x * 0.05;
		data->player->player_pos_y += data->vec->plane_y * 0.05;
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


