/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:32:19 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/04 15:49:21 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libs/MLX42/include/MLX42/MLX42.h"
# include "./libs/libft/libft.h"
# include <math.h>

//=====ASCII COLORS======
# define RED     "\x1b[31m"
# define BOLD    "\x1b[1m"
# define RESET   "\x1b[0m"
# define YELLOW  "\x1b[33m"
# define GREEN   "\x1b[32m"

//======DEFINE TRUTH=====
# define MALAKA true

typedef enum s_map_data
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEILING_COLOR
}	t_map_data;

typedef struct s_gcobj
{
	void			*ptr;
	int				marked;
	struct s_gcobj	*next;
}	t_gcobj;

typedef struct s_gc
{
	t_gcobj	*objects;
	void	**roots[100];
	int		root_count;
}	t_gc;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		height;
	int32_t		width;
	char		**map;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		**floor_color;
	char		**ceiling_color;
	double		player_pos[2]; // change to double (for raycasting precision)
	t_gc		gc;
}	t_data;

typedef struct s_vector
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_vector;

// all variables needed for each ray to cast from the player’s view.
// TODO: initialize!
typedef struct s_ray
{
	// for ray position & direction
	double	camera_x; // camera space
	double	ray_dir_x;
	double	ray_dir_y;

	// length of ray from current position to next x or y-side
	double	dist_pos_to_x; // TODO: check naming
	double	dist_pos_to_y;

	// length of ray from one x or y-side to next x or y-side
	double	dist_next_xgrid; // deltaDistX
	double	dist_next_ygrid; // deltaDistY

}	t_ray;

//==================================UTILS=======================================

char	*get_next_line(t_data *data, int fd);
int		ft_isspace(int c);

//================================VALIDATION====================================

void	init_cube(int ac, char **av, t_data *data);

//==================================ERROR=======================================

void	ft_error(t_data *data, char *error, bool mlx_err);

//=================================COLORS=======================================

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//=================================RENDER=======================================

void	ft_randomize(void *param);

//=================================HOOKS========================================

void	ft_hook_keys(void *param);

//============================GARBAGE_COLLECTOR=================================

void	*gc_malloc(t_gc *gc, size_t size);
void	gc_destroy(t_gc *gc);
t_gc	gc_new(void);
void	gc_collect(t_gc *gc);
char	*gc_strdup(t_gc *gc, const char *s);
void	gc_add_root(t_gc *gc, void **ptr);
char	*gc_strjoin(t_gc *gc, char *s1, char *s2);

//=================================DEBUG========================================

void	d(void);



void	setup_player(t_data *data, t_vector *vec);
void	raycasting(t_data *data, t_ray *ray, t_vector *vec);


#endif // !CUBE3D_H
