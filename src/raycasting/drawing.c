/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:58:47 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/26 22:10:31 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

uint32_t	get_wall_color(t_ray *ray);

/*
creates the 3D perspective illusion by:
- drawing walls at appropriate heights based on distance
- filling the rest with ceiling/floor colors
- creating "hallway-walking" perspective of raycasting engines
*/
void	draw_ceiling_floor_wall(t_data *data, int screen_x)
{
	int			screen_y;
	uint32_t	wall_color;

	wall_color = get_wall_color(data->ray);
	screen_y = 0;
	while (screen_y < data->ray->draw_start)
	{
		mlx_put_pixel(data->image, screen_x, screen_y, ft_pixel(0, 255, 0,
				255));
		screen_y++;
	}
	while (screen_y <= data->ray->draw_end)
	{
		mlx_put_pixel(data->image, screen_x, screen_y, wall_color);
		screen_y++;
	}
	screen_y = data->ray->draw_end;
	while (screen_y < data->height)
	{
		mlx_put_pixel(data->image, screen_x, screen_y, ft_pixel(255, 0, 0,
				255));
		screen_y++;
	}
}

/*
colors wall sides differently for easier visuals
EAST_WEST wall: light blue
NORTH_SOUTH wall: darker blue
*/
uint32_t	get_wall_color(t_ray *ray)
{
	if (ray->wall_side == EAST_WEST)
		return (0x0000FFFF);
	else
		return (0x000080FF);
}
