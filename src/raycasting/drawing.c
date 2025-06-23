/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:58:47 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/23 19:17:18 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"

int	get_wall_color(t_ray *ray);

/*
creates the 3D perspective illusion by:
- drawing walls at appropriate heights based on distance
- filling the rest with ceiling/floor colors
- creating "hallway-walking" perspective of raycasting engines
*/

mlx_image_t	*select_texture(t_data *data, t_ray *ray)
{
	mlx_image_t	*texture;

	if (ray->wall_side == EAST)
		texture = data->textures->e_img;
	else if (ray->wall_side == NORTH)
		texture = data->textures->n_img;
	else if (ray->wall_side == SOUTH)
		texture = data->textures->s_img;
	else
		texture = data->textures->w_img;
	return (texture);
}

uint32_t get_pixel_from_texture(mlx_image_t *tex, int x, int y)
{
	return tex->pixels[y * tex->width + x];
}

void	draw_ceiling_floor_wall(t_data *data, int screen_x)
{
    int          screen_y;
    mlx_image_t *texture;
    int          tex_x;
    double       step, tex_pos;
    uint32_t     color;

    screen_y = 0;
    while (screen_y < data->ray->draw_start)
    {
        mlx_put_pixel(data->image, screen_x, screen_y,
            ft_pixel(data->textures->red_ceiling,
                     data->textures->green_ceiling,
                     data->textures->blue_ceiling,
                     255));
        screen_y++;
    }

    texture = select_texture(data, data->ray);

	double wall_x; // where exactly the wall was hit
	if (data->ray->wall_side == NORTH || data->ray->wall_side == SOUTH)
		wall_x = data->vec->grid_map_x + data->ray->dist_camvec_wall * data->ray->ray_dir_x;
	else
		wall_x = data->vec->grid_map_y + data->ray->dist_camvec_wall * data->ray->ray_dir_y;
	wall_x -= floor(wall_x); // get fractional part (0.0 to 1.0)
	
	tex_x = (int)(wall_x * (double)texture->width + 0.5);
    if ((data->ray->wall_side == EAST && data->ray->ray_dir_x < 0) ||
        (data->ray->wall_side == SOUTH && data->ray->ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;

    step    = (double)texture->height  * 10000 / (double)data->ray->wall_height;
	tex_pos = (data->ray->draw_start - data->height / 2.0 + data->ray->wall_height / 2.0) * step;
    screen_y = data->ray->draw_start;
	int tex_y;
    while (screen_y <= data->ray->draw_end)
    {
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;

        color = get_pixel_from_texture(texture, tex_x, tex_y);
        mlx_put_pixel(data->image, screen_x, screen_y, color);

        screen_y++;
    }

    while (screen_y < data->height)
    {
        mlx_put_pixel(data->image, screen_x, screen_y,
            ft_pixel(data->textures->red_floor,
                     data->textures->green_floor,
                     data->textures->blue_floor,
                     255));
        screen_y++;
    }
}



/*
colors wall sides differently for easier visuals
EAST_WEST wall: light blue
NORTH_SOUTH wall: darker blue
// TODO: remove after textures?
*/
int	get_wall_color(t_ray *ray)
{
	if (ray->wall_side == EAST_WEST)
		return (0x0000FFFF);
	else
		return (0x000080FF);
}
