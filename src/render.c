/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:15:44 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/10 15:27:47 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	render_direction_ray(void *param)
{
	t_data	*data = (t_data *)param;
	int		i, draw_x, draw_y;
	float	x, y, dx, dy;
	int		tile_height = data->height / 50;
	int		length = 50;  // how many steps to draw
	
	x = data->player->player_pos_x * tile_height + tile_height / 2.0f;
	y = data->player->player_pos_y * tile_height + tile_height / 2.0f;
	dx = cosf(data->player->player_angle);
	dy = sinf(data->player->player_angle);
	i = -1;
	while (++i < length)
	{
		draw_x = (int)roundf(x);
		draw_y = (int)roundf(y);
		if (draw_x >= 0 && draw_x < data->width
			&& draw_y >= 0 && draw_y < data->height)
			mlx_put_pixel(data->image, draw_x, draw_y,
				ft_pixel(180, 180, 180, 255));
		x -= dx;
		y -= dy;
	}
}

void	render_player(void *param)
{
	int		i;
	int		j;
	t_data	*data;
	int		tile_height;

	i = -1;
	data = (t_data *)param;
	tile_height = data->height / 50;
	while (++i < tile_height)
	{
		j = -1;
		while (++j < tile_height)
		{
			// if (data->player_pos[1] * tile_height + i + data->player_ofset_x > data->width
			// 	|| data->player_pos[0] * tile_height + j + data->player_ofset_y > data->height)
			// 	return ;
			mlx_put_pixel(data->image, data->player->player_pos_x * tile_height + i,
				data->player->player_pos_y * tile_height + j, ft_pixel(0, 255, 0, 255));
		}
	}
}

static void	scale_image(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	tile_height = data->height / 19;

	i = -1;
	while (++i < tile_height)
	{
		j = -1;
		while (++j < tile_height)
		{
			mlx_put_pixel(data->image, x * tile_height + i, y * tile_height + j, color);
		}
	}
}

void	ft_randomize(void *param)
{
	t_data	*data;
	int		i;
	int		j;
	int		color;

	data = (t_data *)param;
	i = -1;
	while (++i < 14)
	{
		j = -1;
		while (++j < 33)
		{
			if (data->map[i][j] == '1')
				scale_image(data, j, i, ft_pixel(255, 0, 0, 255));
			else
				scale_image(data, j, i, ft_pixel(0, 0, 0, 255));
		}
	}
}
