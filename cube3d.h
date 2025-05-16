/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:32:19 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/16 10:17:33 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libs/MLX42/include/MLX42/MLX42.h"
# include "./libs/libft/libft.h"

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the 
 * current frame.
 */

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		height;
	int32_t		width;
}	t_data;

//==================================ERROR=======================================

void	ft_error(void);

//=================================COLORS=======================================

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//=================================RENDER=======================================

void	ft_randomize(void *param);

//=================================HOOKS=======================================

void	ft_hook_keys(void *param);

#endif // !CUBE3D_H
