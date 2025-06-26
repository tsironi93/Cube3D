/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:16:58 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/26 21:44:02 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_hook_keys(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_forward(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player_backward(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, 0.05);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, -0.05);
}
