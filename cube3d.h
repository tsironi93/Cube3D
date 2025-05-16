/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:32:19 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/16 18:14:58 by itsiros          ###   ########.fr       */
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

//=====ASCII COLORS======
# define RED     "\x1b[31m"
# define BOLD    "\x1b[1m"
# define RESET   "\x1b[0m"
# define YELLOW  "\x1b[33m"
# define GREEN   "\x1b[32m"

typedef enum s_map_data
{
	NORTH_TEXTURE,
	SOUTH_TEXTURE,
	WEST_TEXTURE,
	EAST_TEXTURE,
	FLOOR_COLOR,
	CEALING_COLOR
}	t_map_data;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		height;
	int32_t		width;
}	t_data;

//==================================UTILS=======================================

char	*get_next_line(int fd);
int		ft_isspace(int c);

//==================================ERROR=======================================

void	ft_error(char *error, bool mlx_err);

//=================================COLORS=======================================

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//=================================RENDER=======================================

void	ft_randomize(void *param);

//=================================HOOKS========================================

void	ft_hook_keys(void *param);

//=================================DEBUG========================================

void	d(void);

#endif // !CUBE3D_H
