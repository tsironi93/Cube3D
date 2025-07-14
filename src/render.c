/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:15:44 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/14 13:35:53 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	scale_image(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile_size;
	int	minimap_x;
	int	minimap_y;

	tile_size = 20;
	i = -1;
	while (++i < tile_size)
	{
		j = -1;
		while (++j < tile_size)
		{
			minimap_x = x * tile_size + i + 4;
			minimap_y = y * tile_size + j + 4;
			if (minimap_x >= 0 && minimap_x < data->width
				&& minimap_y >= 0 && minimap_y < data->height)
				mlx_put_pixel(data->image, x * tile_size + i,
					y * tile_size + j, color);
		}
	}
}

void	render_minimap(void *param)
{
	t_data	*data;
	int		i;
	int		j;

	data = (t_data *)param;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				scale_image(data, j, i, ft_pixel(255, 0, 0, 255));
			else if (i == (int)data->player->player_pos_x
				&& j == (int)data->player->player_pos_y)
				scale_image(data, j, i, ft_pixel(0, 255, 0, 255));
			else
				scale_image(data, j, i, ft_pixel(30, 30, 30, 255));
			j++;
		}
		i++;
	}
}
