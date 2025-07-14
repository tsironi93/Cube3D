/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:58:47 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/13 12:34:48 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"
#include <stdint.h>
/*
creates the 3D perspective illusion by:
- drawing walls at appropriate heights based on distance
- filling the rest with ceiling/floor colors
- creating "hallway-walking" perspective of raycasting engines
*/

mlx_texture_t	*select_texture(t_data *data, t_ray *ray)
{
	mlx_texture_t	*texture;

	if (ray->wall_side == EAST)
		texture = data->textures->east;
	else if (ray->wall_side == NORTH)
		texture = data->textures->north;
	else if (ray->wall_side == SOUTH)
		texture = data->textures->south;
	else
		texture = data->textures->west;
	return (texture);
}

static void	texture_calcs(t_data *data, mlx_texture_t *texture)
{
	if (data->ray->wall_side == NORTH_SOUTH)
		data->wall->wall_x = data->player->player_pos_x
			+ data->ray->dist_camvec_wall * data->ray->ray_dir_x;
	else
		data->wall->wall_x = data->player->player_pos_y
			+ data->ray->dist_camvec_wall * data->ray->ray_dir_y;
	data->wall->wall_x -= floor(data->wall->wall_x);
	data->wall->tex_x = (int)(data->wall->wall_x * (double)texture->width);
// if ((data->ray->wall_side == EAST && data->ray->ray_dir_x > 0) ||
//     (data->ray->wall_side == WEST && data->ray->ray_dir_x < 0) ||
//     (data->ray->wall_side == NORTH && data->ray->ray_dir_y > 0) ||
//     (data->ray->wall_side == SOUTH && data->ray->ray_dir_y < 0))
//     tex_x = texture->width - tex_x - 1;
	data->wall->step = (double)texture->height / (double)data->ray->wall_height;
	data->wall->tex_pos = (data->ray->draw_start - (double)data->height / 2.0
			+ data->ray->wall_height / 2.0) * data->wall->step;
}

static void	draw_y(t_data *data, mlx_texture_t *texture, int screen_x,
				int screen_y)
{
	int32_t	color;

	data->wall->tex_y = (int)data->wall->tex_pos;
	if (data->wall->tex_y >= (int)texture->height)
		data->wall->tex_y = texture->height - 1;
	data->wall->tex_pos += data->wall->step;
	color = get_pixel_from_texture(texture, data->wall->tex_x,
			data->wall->tex_y);
	mlx_put_pixel(data->image, screen_x, screen_y, color);
}

void	draw_ceiling_floor_wall(t_data *data, int screen_x)
{
	int				screen_y;
	mlx_texture_t	*texture;

	screen_y = 0;
	while (screen_y < data->ray->draw_start)
		mlx_put_pixel(data->image, screen_x, screen_y++,
			ft_pixel(data->textures->red_ceiling,
				data->textures->green_ceiling, data->textures->blue_ceiling,
				255));
	texture = select_texture(data, data->ray);
	texture_calcs(data, texture);
	screen_y = data->ray->draw_start;
	while (screen_y <= data->ray->draw_end)
		draw_y(data, texture, screen_x, screen_y++);
	while (screen_y < data->height)
		mlx_put_pixel(data->image, screen_x, screen_y++,
			ft_pixel(data->textures->red_floor, data->textures->green_floor,
				data->textures->blue_floor, 255));
}
