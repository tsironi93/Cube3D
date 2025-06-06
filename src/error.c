/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:11:03 by itsiros           #+#    #+#             */
/*   Updated: 2025/06/06 18:15:10 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_error(t_data *data, char *error, bool mlx_err)
{
	write(2, BOLD RED, sizeof(BOLD RED) - 1);
	if (error)
		write(2, error, ft_strlen(error));
	if (mlx_err)
		printf("%s", mlx_strerror(mlx_errno));
	write(2, "\n", 1);
	write(2, RESET, sizeof(RESET) - 1);
	gc_collect(&data->gc);
	exit(EXIT_FAILURE);
}
