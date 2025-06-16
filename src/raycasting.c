/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/16 19:28:01 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/raycasting.h"

// if coordinates are within the map bounds
bool is_map_coordinates(int x, int y, t_data *data)
{
    if (!(x >= 0 && x < data->map_height))
        return (false);
    if (!(data->map[x] != NULL && y >= 0 && y < (int)ft_strlen(data->map[x])))
    	return (false);
    return (true);
}

// call ft if needed when walking through wall or ray shoots through wall any other than the first one
bool inside_of_walls(int x, int y, t_data *data)
{
    if (is_map_coordinates(x, y, data) == false)
        return (false);
    if (data->map[x][y] == '1' || data->map[x][y] == 'F')
        return (true);
    return(false);
}

// NOTES:
// seperate variables for x and y?
//   playerpos0 -> x (player_pos.x) / player_pos_X
//   playerpos1 -> y (player_pos.y) / player_pos_Y
//  initial player setup (dir, plane, pos) at game start
// (PLAYER FACES NORTH)
// initialization (all others run in a per-ray, per-frame sense)
void    setup_player(t_data *data)
{
    // starting position of player (X,Y)
    // which box of the map we're in
    data->vec->grid_map_x = data->player->player_pos_x; // player pos not initialized yet (init_mlx after setup_player)
    printf("XXX = %d\n", data->vec->grid_map_x);
    data->vec->grid_map_y = data->player->player_pos_y;
    printf("YYY = %d\n", data->vec->grid_map_y);
    // initial direction vector (X,Y)
    data->vec->dir_x = 0;
    data->vec->dir_y = -1;
    // camera FOV plane (X,Y)
    data->vec->plane_x = 0.66;
    data->vec->plane_y = 0;
}

/*
setup/calculate ray position and direction for each column at every frame
creates a set of rays fanning out
    from the player's position to simulate the 3D perspective.
-> cast a ray for every pixel of the screens width
initializing part of ray struct
*/
/*
deltaDistX: distance ray has to travel from 1 x-side to the next x-side,
deltaDistY: from 1 y-side to the next y-side.
to travel to cross one full tile along the grid
 -> makes sure to always step forward in distance
initializing part of ray struct
setup grid stepping distances at per-ray (per column)
fabs: returns absolute value of a double
*/
void    calc_ray_pos_dir(t_data *data, t_ray *ray, t_vector *vec, int screen_x)
{
    // double  ray_angle;

    // ray_angle = atan2(ray->ray_dir_y, ray->ray_dir_x) - atan2(vec->dir_y, vec->dir_x);
    // // p->p_directionx IS vec->dir_x

    // ray->dist_camvec_wall *= cos(ray_angle);
    
    ray->camera_x = 2 * screen_x / (double)data->width - 1;
    // printf("ray->camera_x = %f\n", ray->camera_x); // 0
    // printf("screen_x = %d\n", screen_x);
    ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
    // printf("ray_dir_x = %f\n", ray->ray_dir_x);
    ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;
    // printf("ray_dir_yw = %f\n", ray->ray_dir_x);
    // printf("vec->dir_y = %f\n", vec->dir_y);
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

//  *calculate step and initial sideDist*
// calculate side_dist_x & y
// -> distance to next vertical/horizontal gridline
// calculate stepx, stepy (either +1 or -1)
// -> which direction ray is stepping in grid
/*
1. Setting the step direction (left/right or up/down).
2. Calculating how far the ray has to travel to hit
the first vertical or horizontal grid line.
*/
void prepare_dda(t_data *data, t_ray *ray, t_vector *vec)
{
    // case 1 X-direction: ray going left
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (data->player->player_pos_x - vec->grid_map_x) * ray->delta_dist_x;
    }
    // case 2 X-direction: ray going right
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (vec->grid_map_x + 1.0 - data->player->player_pos_x) * ray->delta_dist_x;
    }
    // case 3 Y-direction: ray going up
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (data->player->player_pos_y - vec->grid_map_y) * ray->delta_dist_y;
    }
    // case 4 Y-direction: ray going down
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (vec->grid_map_y + 1.0 - data->player->player_pos_y) * ray->delta_dist_y;
    }
}

// DDA algo starts
/*
variables
-hit: determines whether or not loop may be ended
-side: contains if an x-side or y-side (borders btw two squares) of a wall was hit
        -> set to 0, if x-side hit
        -> set to 1, if y-side ht
*/
void run_dda_algorithm(t_data *data, t_ray *ray, t_vector *vec)
{
    bool ray_hit_wall;
    // printf("map value: %c\n", ((data->map[vec->grid_map_x][vec->grid_map_y])));
    // printf("side_dist_x: %f, side_dist_y: %f\n", ray->side_dist_x, ray->side_dist_y);
    // printf("delta_dist_x: %f, delta_dist_y: %f\n", ray->delta_dist_x, ray->delta_dist_y);
    // printf("ray->step_x: %d, ray->step_y: %d\n", ray->step_x, ray->step_y);
    // printf("grid_map_x: %d, grid_map_y: %d\n", vec->grid_map_x, vec->grid_map_y);
    // printf("************************************************************\n");
    ray_hit_wall = false;
    while (ray_hit_wall == false)
    {
        if (is_map_coordinates(vec->grid_map_x, vec->grid_map_y, data) == false) // TODO: delete if after scaling map?
            break; // if outside of map, break loop
        // goes to next map grid (x-direction or y-direction)
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            vec->grid_map_x += ray->step_x;
            ray->wall_side = EAST_WEST;
        }
        else
        {
            ray->side_dist_y +=ray->delta_dist_y; // 1
            vec->grid_map_y += ray->step_y; // 0
            ray->wall_side = NORTH_SOUTH;
        }
        if (is_map_coordinates(vec->grid_map_x, vec->grid_map_y, data) == true)
        {
            if (data->map[vec->grid_map_x][vec->grid_map_y] == '1')
            {
				// printf("ray hit wall at x: %d, y: %d\n", vec->grid_map_x, vec->grid_map_y);
                ray_hit_wall = true;
            }
        }
    }
}

/*
camera plane vector
- calculate distance of the ray to the wall
    -> to calculate how high the wall has to be drawn after
- to eliminate fish eye effect: calc distance from plane to wall, NOT player to wall
- dist_camvec_wall: distance btw wall and camera vector
*/
void calc_wall_height(t_ray *ray)
{
    if (ray->wall_side == EAST_WEST)
    {
        ray->dist_camvec_wall = ray->side_dist_x - ray->delta_dist_x;
        // printf("dist wall0 = %f\n", ray->dist_camvec_wall);
    }
    else
    {
        ray->dist_camvec_wall = ray->side_dist_y - ray->delta_dist_y;
        // printf("dist wall1 = %f\n", ray->dist_camvec_wall);
    }
}

void    raycasting(void *param)
{
    t_data	*data = (t_data *)param;

    int screen_x; // moves across horizontally
    int line_height;
    int draw_start;
    int draw_end;
    int screen_y;
    double  ray_angle;
	
    screen_x = 0;
    while (screen_x < data->width)
    {
        // printf("Casting ray at column: %d\n", screen_x); 
        calc_ray_pos_dir(data, data->ray, data->vec, screen_x);
        prepare_dda(data, data->ray, data->vec);
        run_dda_algorithm(data, data->ray, data->vec);
        
        ray_angle = atan2(data->ray->ray_dir_y, data->ray->ray_dir_x) - atan2(data->vec->dir_y, data->vec->dir_x);
        // p->p_directionx IS vec->dir_x
        data->ray->dist_camvec_wall *= cos(ray_angle);
        
        calc_wall_height(data->ray);
        
        // printf("dist wall = %f\n", data->ray->dist_camvec_wall);

        double dist = data->ray->dist_camvec_wall;
        const double EPS = 1e-6; // to avoid division by 0
        if (dist < EPS) 
            dist = EPS;
        line_height = (int)(data->height / dist);

        // line_height = data->height / data->ray->dist_camvec_wall;
        draw_start = data->height / 2 - line_height / 2;
        draw_end = data->height / 2 + line_height / 2;
        
        if (draw_start < 0)
            draw_start = 0;
        if (draw_end >= data->height)
            draw_end = data->height - 1;

        screen_y = 0;
        // printf("data->image->HEIGHT %d\n", data->image->height);
        // printf("data->image->WIDTH %d\n", data->image->width);
        while (screen_y < draw_start) 
        {   
            mlx_put_pixel(data->image, screen_x, screen_y,  ft_pixel(0, 255, 0, 255)); // green
            screen_y++;
        }
        screen_y = draw_start;
        while (screen_y < draw_end)
        {
            mlx_put_pixel(data->image, screen_x, screen_y, 0x0000FFFF); // blue
            screen_y++;
        }
        screen_y = draw_end;
        while (screen_y < data->height)
        {
            mlx_put_pixel(data->image, screen_x, screen_y, ft_pixel(255, 0, 0, 255)); // red
            screen_y++;
        }
        screen_x++;
    }
}
