/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:44:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/06/18 16:03:06 by pdrettas         ###   ########.fr       */
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

//  initial player setup (dir, plane, pos) at game start
// (PLAYER FACES NORTH)
// initialization (all others run in a per-ray, per-frame sense)
void    setup_player(t_data *data)
{
    // starting position of player (X,Y)
    // which box of the map we're in
    data->vec->grid_map_x = (int)data->player->player_pos_x; 
    data->vec->grid_map_y = (int)data->player->player_pos_y;
    printf("Player pos: x=%f, y=%f\n", data->player->player_pos_x, data->player->player_pos_y);
    printf("Grid pos: x=%d, y=%d\n", data->vec->grid_map_x, data->vec->grid_map_y);
    // initial direction vector (X,Y) (where player is looking)
    data->vec->dir_x = 0;
    data->vec->dir_y = -1;
    // camera FOV plane (X,Y)
    data->vec->plane_x = 0.66;
    data->vec->plane_y = 0;
}

/*
setup/calculate ray position and direction for each column at every frame
creates a set of rays fanning out from the player's position to simulate the 3D perspective.
-> cast a ray for every pixel of the screens width
deltaDistX: distance ray has to travel from 1 x-side to the next x-side,
deltaDistY: from 1 y-side to the next y-side.
to travel to cross one full tile along the grid
 -> makes sure to always step forward in distance
setup grid stepping distances at per-ray (per column)
fabs: returns absolute value of a double
*/
void    calc_ray_pos_dir(t_data *data, t_ray *ray, t_vector *vec, int screen_x)
{
    // double  ray_angle;

    ray->camera_x = 2 * screen_x / (double)data->width - 1; // in which direction ray is pointing for this pixel column x on screen (column x 0 (far left), 320 straight, 639 right)
    // it decides what wall (and how far) he ray will hit in the game world. WHICH then decides how tall the vertical line will be for that column
    ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
    ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;
    
    // ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    // ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    // calculating delta distances to avoid division by zero
    // delta distance represents how far a ray travels to cross one grid square.
    // When the ray direction is 0 (ray going perfectly horizontal or vertical), we set delta distance to a very large number instead of dividing by zero, 
    // which prevents crashes and ensures the DDA algorithm correctly steps only in the direction the ray is actually moving.
    if (ray->ray_dir_x == 0) // (NEW) if
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
        
    if (ray->ray_dir_y == 0) // (NEW) if
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    
    // fish eye correction (TODO: move somewhere else)
    // ray_angle = atan2(data->ray->ray_dir_y, data->ray->ray_dir_x) - atan2(data->vec->dir_y, data->vec->dir_x);
    // data->ray->dist_camvec_wall *= cos(ray_angle);
}

//  *calculate step and initial sideDist*
// calculate side_dist_x & y -> distance to next vertical/horizontal gridline
// calculate stepx, stepy (either +1 or -1) -> which direction ray is stepping in grid
/*
1. Setting the step direction (left/right or up/down).
2. Calculating how far the ray has to travel to hit
the first vertical or horizontal grid line.
*/
void prepare_dda(t_data *data, t_ray *ray, t_vector *vec)
{
    // resetting grid position for each ray (NEW)
    // since DDA algo modifies these values, so have to start fresh for each ray
    vec->grid_map_x = (int)data->player->player_pos_x;
    vec->grid_map_y = (int)data->player->player_pos_y;
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
    int iterations;
    int max_iterations;
    
    max_iterations = data->map_height + data->width; // prevent infinite loop (NEW)
    iterations = 0;
    ray_hit_wall = false;
    while (ray_hit_wall == false && iterations < max_iterations)
    {
        iterations++;
        // if (is_map_coordinates(vec->grid_map_x, vec->grid_map_y, data) == false) // TODO: delete if after scaling map? *DONE*
        //     break; // if outside of map, break loop
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
        // if ray has hit a wall
        if (!is_map_coordinates(vec->grid_map_x, vec->grid_map_y, data))
        {
            ray_hit_wall = true;  // putting out of bounds as wall (NEW)
        }
        else if (data->map[vec->grid_map_x][vec->grid_map_y] == '1')
        {
            ray_hit_wall = true;
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
    // mininum distance to prevent division by 0 (NEW)
    if (ray->dist_camvec_wall < 0.01)
        ray->dist_camvec_wall = 0.01;
}

// colors wall sides differently for easier visuals
uint32_t get_wall_color(t_ray *ray) // (NEW)
{
    if (ray->wall_side == EAST_WEST)
        return 0x0000FFFF;  // blue (vertical)
    else
        return 0x000080FF;  // darker blue (horizontal)
}

void draw_ceiling_floor_wall(t_data	*data, int screen_x)
{
    int line_height;
    // double dist;
    int draw_start;
    int draw_end;
    int screen_y;
    uint32_t wall_color;

    // to avoid division by 0
    // dist = data->ray->dist_camvec_wall;
    // const double EPS = 1e-6; 
    // if (dist < EPS) 
    //     dist = EPS;
    // line_height = (int)(data->height / dist);
    
    line_height = (int)data->height / data->ray->dist_camvec_wall;
    draw_start = (data->height - line_height) / 2;
    draw_end = (data->height + line_height) / 2;
    
    // making sure drawing of line doesnt go off screen
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= data->height)
        draw_end = data->height - 1;
    
    wall_color = get_wall_color(data->ray);
    // drawing vertical line at column x from draw_start to draw_end
    screen_y = 0;
    // printf("data->image->HEIGHT %d\n", data->image->height);
    // printf("data->image->WIDTH %d\n", data->image->width);
    while (screen_y < draw_start) 
    {   
        mlx_put_pixel(data->image, screen_x, screen_y,  ft_pixel(0, 255, 0, 255)); // green ceiling
        screen_y++;
    }
    // screen_y = draw_start;
    while (screen_y <= draw_end)
    {
        mlx_put_pixel(data->image, screen_x, screen_y, wall_color); // blue wall
        screen_y++;
    }
    screen_y = draw_end;
    while (screen_y < data->height)
    {
        mlx_put_pixel(data->image, screen_x, screen_y, ft_pixel(255, 0, 0, 255)); // red floor
        screen_y++;
    } 
}

void    raycasting(void *param)
{
    t_data	*data = (t_data *)param;

    int screen_x; // moves across horizontally
    
    screen_x = 0;
    while (screen_x < data->width)
    {
        calc_ray_pos_dir(data, data->ray, data->vec, screen_x);
        prepare_dda(data, data->ray, data->vec);
        run_dda_algorithm(data, data->ray, data->vec);
        calc_wall_height(data->ray);
        draw_ceiling_floor_wall(data, screen_x);
        printf("XXX = %d\n", data->vec->grid_map_x);
        printf("YYY = %d\n", data->vec->grid_map_y);
        screen_x++;
    }
}

// IN MAP (x is down, y is right)