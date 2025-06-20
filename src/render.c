/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:15:44 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/19 18:24:48 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	render_direction_ray(void *param)
{
	t_data	*data = (t_data *)param;
	int		i, draw_x, draw_y;
	float	x, y, dx, dy;
	int		tile_height = 5;
	int		length = 50;  // how many steps to draw
	
	x = data->player->player_pos_x * tile_height + tile_height / 2.0f;
	y = data->player->player_pos_y * tile_height + tile_height / 2.0f;
	dx = cosf(data->player->player_angle);
	dy = sinf(data->player->player_angle);
	i = -1;
	while (++i < length)
	{
		// printf("distance to wall = %f\n", data->ray->dist_camvec_wall);
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
			minimap_x = x * tile_size + i + 5;
			minimap_y = y * tile_size + j + 5;
			if (minimap_x >= 0 && minimap_x < data->width
				&& minimap_y >= 0 && minimap_y < data->height)
				mlx_put_pixel(data->image, x * tile_size + i,
				  y * tile_size + j, color);
		}
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
	tile_height = 5;
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

static void	minimap(void *param)
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
			else if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				mlx_put_pixel(data->image, data->player->player_pos_x * 5 + i,
				data->player->player_pos_y * 5 + j, ft_pixel(0, 255, 0, 255));
			else
				scale_image(data, j, i, ft_pixel(0, 0, 0, 255));
			j++;
		}
		i++;
	}
}

void render_minimap(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	minimap(data);
	// render_player(data);
	render_direction_ray(data);
}
