/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:16:58 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/16 13:56:57 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_hook_keys(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) // forward
	{
		data->player->player_pos_x += data->player->player_delta_x;
		data->player->player_pos_y += data->player->player_delta_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) // backward
	{
		data->player->player_pos_x -= data->player->player_delta_x;
		data->player->player_pos_y -= data->player->player_delta_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) // strafe left 
	{
		data->player->player_pos_x -= data->player->player_delta_y;
		data->player->player_pos_y += data->player->player_delta_x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) // strafe right
	{
		data->player->player_pos_x += data->player->player_delta_y;
		data->player->player_pos_y -= data->player->player_delta_x;
	}
	// rotation
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) // rotates left
	{
		data->player->player_angle -= 0.1;
		if (data->player->player_angle < 0)
			data->player->player_angle += 2 * PI;
		data->player->player_delta_x = cos(data->player->player_angle);
		data->player->player_delta_y = sin(data->player->player_angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) // rotates right
	{
		data->player->player_angle += 0.1;
		if (data->player->player_angle > 2 * PI)
			data->player->player_angle -= 2 * PI;
		data->player->player_delta_x = cos(data->player->player_angle);
		data->player->player_delta_y = sin(data->player->player_angle);
	}
}
