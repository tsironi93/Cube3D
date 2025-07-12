/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:32:19 by itsiros           #+#    #+#             */
/*   Updated: 2025/07/12 11:10:59 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/raycasting.h"

//=====ASCII COLORS======
# define RED "\x1b[31m"
# define BOLD "\x1b[1m"
# define RESET "\x1b[0m"
# define YELLOW "\x1b[33m"
# define GREEN "\x1b[32m"

//======DEFINE TRUTH=====
# define MALAKA true
# define PI 3.14159265358979323846

typedef enum s_map_data
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR
}					t_map_data;

typedef struct s_gcobj
{
	void			*ptr;
	int				marked;
	struct s_gcobj	*next;
}					t_gcobj;

typedef struct s_gc
{
	t_gcobj	*objects;
	void	**roots[100];
	int		root_count;
}	t_gc;

typedef struct s_player
{
	float	player_pos_x;
	float	player_pos_y;
	float	player_delta_x;
	float	player_delta_y;
	float	player_angle;
}	t_player;

typedef struct s_textures
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			**floor_color;
	char			**ceiling_color;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_image_t		*n_img;
	mlx_image_t		*s_img;
	mlx_image_t		*w_img;
	mlx_image_t		*e_img;
	int				red_floor;
	int				green_floor;
	int				blue_floor;
	int				red_ceiling;
	int				green_ceiling;
	int				blue_ceiling;
}	t_textures;

typedef struct s_data
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	struct s_textures	*textures;
	int32_t				height;
	int32_t				width;
	char				**map;
	int					map_width;
	int					map_height;
	int					player_pos[2];
	float				player_ofset_x;
	float				player_ofset_y;
	t_player			*player;
	t_ray				*ray;
	t_vector			*vec;
	t_gc				gc;
}	t_data;

//==================================UTILS=======================================

int		ft_isspace(int c);

//================================VALIDATION====================================

void	init_cube(int ac, char **av, t_data *data);
bool	flood_check(t_data *data, char **map, int y, int x);
char	**clone_map(t_data *data, char **map);
void	find_player_pos(t_data *data, char **map);

//==================================ERROR=======================================

void	ft_error(t_data *data, char *error, bool mlx_err);

//=================================COLORS=======================================

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//=================================RENDER=======================================

void	render_minimap(void *param);

//=================================HOOKS========================================

void	ft_hook_keys(void *param);
void	rotate_player(t_data *data, double rotation_speed);
void	move_player_forward(t_data *data);
void	move_player_backward(t_data *data);
void	move_player_right(t_data *data);
void	move_player_left(t_data *data);

//============================GARBAGE_COLLECTOR=================================

void	*gc_malloc(t_gc *gc, size_t size);
void	gc_destroy(t_gc *gc);
t_gc	gc_new(void);
void	gc_collect(t_gc *gc);
char	*gc_strdup(t_gc *gc, const char *s);
void	gc_add_root(t_gc *gc, void **ptr);
char	*gc_strjoin(t_gc *gc, char *s1, char *s2);

//===============================RAYCASTING=====================================

void	setup_player(t_data *data, t_vector *vec);
void	raycasting(void *param);
void	render_frame(void *param);
void	init_structs(t_data *data);
void	draw_images(t_data *data);
bool	is_map_coordinates(int x, int y, t_data *data);
void	debug_map_and_player(t_data *data);
char	*get_next_line(int fd);
bool	inside_of_walls(int x, int y, t_data *data);
void	draw_ceiling_floor_wall(t_data *data, int screen_x);
void	calc_wall_height(t_data *data, t_ray *ray);
void	run_dda_algorithm(t_data *data, t_ray *ray, t_vector *vec);
void	prepare_dda(t_data *data, t_ray *ray, t_vector *vec);
void	calc_ray_pos_dir(t_data *data, t_ray *ray, t_vector *vec,
			int screen_x);
bool	inside_of_walls(int x, int y, t_data *data);
bool	is_map_coordinates(int x, int y, t_data *data);
bool	is_wall_collision(t_data *data, float position_x,
			float position_y);

#endif // !CUBE3D_H
