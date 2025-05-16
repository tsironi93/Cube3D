/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:16:58 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/16 10:17:02 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_hook_keys(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->image->instances[0].y -= 40;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->image->instances[0].y += 40;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->image->instances[0].x -= 40;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->image->instances[0].x += 40;
}
