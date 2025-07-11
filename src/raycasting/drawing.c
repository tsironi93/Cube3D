/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:58:47 by pdrettas          #+#    #+#             */
/*   Updated: 2025/07/11 15:58:42 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"
#include "../../includes/raycasting.h"
#include <stdint.h>

int	get_wall_color(t_ray *ray);

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

uint32_t get_pixel_from_texture(mlx_texture_t *tex, int x, int y)
{
    if (x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
        return 0xFF00FFFF; // magenta (error)
    int index = (y * tex->width + x) * 4;
    return ((uint32_t)tex->pixels[index] << 24)
         | ((uint32_t)tex->pixels[index + 1] << 16)
         | ((uint32_t)tex->pixels[index + 2] << 8)
         | ((uint32_t)tex->pixels[index + 3]);
}
//
// uint32_t    get_wall_pixel(t_data *data, mlx_image_t *tex, t_ray *c , int row)
// {
//     float   line;
//     int     tex_x;
//     int     tex_y;    line = fmaxf((float)data->height / fmaxf(c->dist_camvec_wall, 0.2f), 1.0f);
//
// 	double hitx = data->player->player_pos_x + c->ray_dir_x * c->dist_camvec_wall;
// 	double hity = data->player->player_pos_y + c->ray_dir_y * c->dist_camvec_wall;
//     if (c->wall_side == EAST_WEST)
//         tex_x = (int)((hitx - floorf(hity)) * tex->width);
//     else
//         tex_x = (int)((hitx - floorf(hitx)) * tex->width);
//     if ((c->wall_side == 0 && c->ray_dir_x < 0.0f)
//         || (c->wall_side == 1 && c->ray_dir_y > 0.0f))
//         tex_x = tex->width - tex_x - 1;
//     tex_y = (int)((row + line * 0.5f - data->height * 0.5f)
//             * ((float)tex->height / line));
//     if (tex_y < 0)
//         tex_y = 0;
//     else if (tex_y >= (int)tex->height)
//         tex_y = tex->height -1;
//     return (((uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * 4] << 24)
//         | ((uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * 4 + 1] << 16)
//         | ((uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * 4 + 2] << 8)
//         | (uint32_t)tex->pixels[(tex_y * tex->width + tex_x) * 4 + 3]);
// }

void	draw_ceiling_floor_wall(t_data *data, int screen_x)
{
    int          screen_y;
    mlx_texture_t *texture;
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
		wall_x = data->player->player_pos_x + data->ray->dist_camvec_wall * data->ray->ray_dir_x;
	else
		wall_x = data->player->player_pos_y + data->ray->dist_camvec_wall * data->ray->ray_dir_y;
	wall_x -= floor(wall_x); // get fractional part (0.0 to 1.0)

	tex_x = (int)(wall_x * (double)texture->width);
	if ((data->ray->wall_side == EAST && data->ray->ray_dir_x > 0) ||
        (data->ray->wall_side == WEST && data->ray->ray_dir_x < 0) ||
        (data->ray->wall_side == NORTH && data->ray->ray_dir_y > 0) ||
        (data->ray->wall_side == SOUTH && data->ray->ray_dir_y < 0))
        tex_x = texture->width - tex_x - 1;



    step = (double)texture->height / (double)data->ray->wall_height;

	// draw the wall
	tex_pos = (data->ray->draw_start - (double)data->height / 2.0 + data->ray->wall_height / 2.0) * step;
    screen_y = data->ray->draw_start;
	int tex_y;
    while (screen_y <= data->ray->draw_end)
    {
		tex_y = (int)tex_pos;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		
		// get the pixel color from the texture
		// color = get_wall_pixel(data, texture, data->ray, screen_y);
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
