/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:58:47 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/12 10:49:11 by itsiros          ###   ########.fr       */
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

uint32_t	get_pixel_from_texture(mlx_texture_t *tex, int x, int y)
{
	int	index;

	if (x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
		return (0xFF00FFFF);
	index = (y * tex->width + x) * 4;
	return (((uint32_t)tex->pixels[index] << 24)
		| ((uint32_t)tex->pixels[index + 1] << 16)
		| ((uint32_t)tex->pixels[index + 2] << 8)
		| ((uint32_t)tex->pixels[index + 3]));
}

void	draw_ceiling_floor_wall(t_data *data, int screen_x)
{
	int				screen_y;
	mlx_texture_t	*texture;
	int				tex_x;
	double			step, tex_pos;
	uint32_t		color;

	screen_y = 0;
	while (screen_y < data->ray->draw_start)
	{
		mlx_put_pixel(data->image, screen_x, screen_y,
			ft_pixel(data->textures->red_ceiling,
				data->textures->green_ceiling, data->textures->blue_ceiling,
				255));
		screen_y++;
	}
	texture = select_texture(data, data->ray);
	double wall_x;
	if (data->ray->wall_side == NORTH_SOUTH)
		wall_x = data->player->player_pos_x + data->ray->dist_camvec_wall * data->ray->ray_dir_x;
	else
		wall_x = data->player->player_pos_y + data->ray->dist_camvec_wall * data->ray->ray_dir_y;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	// if ((data->ray->wall_side == EAST && data->ray->ray_dir_x > 0) ||
    //     (data->ray->wall_side == WEST && data->ray->ray_dir_x < 0) ||
    //     (data->ray->wall_side == NORTH && data->ray->ray_dir_y > 0) ||
    //     (data->ray->wall_side == SOUTH && data->ray->ray_dir_y < 0))
    //     tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / (double)data->ray->wall_height;
	tex_pos = (data->ray->draw_start - (double)data->height / 2.0 + data->ray->wall_height / 2.0) * step;
	screen_y = data->ray->draw_start;
	int tex_y;
	while (screen_y <= data->ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		color = get_pixel_from_texture(texture, tex_x, tex_y);
		mlx_put_pixel(data->image, screen_x, screen_y, color);
		screen_y++;
	}
	while (screen_y < data->height)
	{
		mlx_put_pixel(data->image, screen_x, screen_y,
			ft_pixel(data->textures->red_floor, data->textures->green_floor,
				data->textures->blue_floor, 255));
		screen_y++;
	}
}
