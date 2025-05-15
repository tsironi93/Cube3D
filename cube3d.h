/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:32:19 by itsiros           #+#    #+#             */
/*   Updated: 2025/05/15 13:41:28 by itsiros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libs/MLX42/include/MLX42/MLX42.h"
# include "./libs/libft/libft.h"
# define WIDTH 1024
# define HEIGHT 1024

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the 
 * current frame.
 */

typedef struct s_mlx
{
	void	*window;
	void	*context;
	int32_t	*width;
	int32_t	height;
	double	delta_time;
}	t_mlx;

#endif // !CUBE3D_H
